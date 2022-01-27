package db;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/** テーブルbook用DAO */
public class BookDAO {
	/** プログラム起動時に一度だけ実行 */
	static {
		try {
			Class.forName("org.h2.Driver"); //JDBC Driver読込
		} catch (Exception e) {
		e.printStackTrace();
		}
	}
	/** 全表示 */
	public List<Book> findAll(String item, String order, String search_d, String search_g) {
		List<Book> list = new ArrayList<>();
		String url = "jdbc:h2:tcp://localhost/j:/h2/s1932134";
		Connection conn = null;
		try {
			conn = DriverManager.getConnection(url, "user", "pass");
			String sql = "SELECT * from book";
			//検索
			if (search_d != null && search_g != null) {
				System.out.printf("実行");
				String s = " WHERE 電子対応='"+search_d+"'"+" AND ジャンル='"+search_g+"'";
			sql += s;

			//並び替え
			}else if (item != null && order != null) {
				String s = " ORDER BY "+item;//並び替えに使う要素item 昇順（デフォルト）
				if (order.equals("desc")) {s += " DESC";}//降順
			sql += s;
			}
			PreparedStatement pre = conn.prepareStatement(sql);
			ResultSet rs = pre.executeQuery();
			while (rs.next()) {
				int id = rs.getInt("ID");
				String title = rs.getString("書籍名");
				String name = rs.getString("著者名");
				int date = rs.getInt("発行年");;
				String genre = rs.getString("ジャンル");
				int price = rs.getInt("価格");
				int point = rs.getInt("評価");
				String denshi = rs.getString("電子対応");
				Book a = new Book(id, title, name, date, genre, price, point, denshi);
				list.add(a);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			if (conn != null) {
				try {
					conn.close();
					} catch (SQLException e) {
						e.printStackTrace();
						return null;
					}
				}
			}
		return list;
		}

	/** 追加(IDは自動生成) */
	public boolean insert(String title, String name, int date,
			String genre, int price, int point, String denshi) {
	String url = "jdbc:h2:tcp://localhost/j:/h2/s1932134";
	Connection conn = null;
	try {
		conn = DriverManager.getConnection(url, "user", "pass");
		String sql = "INSERT INTO book(書籍名,著者名,発行年,ジャンル,価格,評価,電子対応) VALUES(?,?,?,?,?,?,?)";
		PreparedStatement pre = conn.prepareStatement(sql);
		pre.setString(1, title);
		pre.setString(2, name);
		pre.setInt(3, date);
		pre.setString(4, genre);
		pre.setInt(5, price);
		pre.setInt(6, point);
		pre.setString(7, denshi);
		int result = pre.executeUpdate();
		if (result == 1) return true;
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					e.printStackTrace();
				}
			}
		}
	 return false;
	 }

	/** 削除 */
	public boolean delete(int id) {
		String url = "jdbc:h2:tcp://localhost/j:/h2/s1932134";
		Connection conn = null;
		try {
			conn = DriverManager.getConnection(url, "user", "pass");
			String sql = "DELETE FROM book WHERE ID=?";
			PreparedStatement pre = conn.prepareStatement(sql);
			pre.setInt(1, id);
			int result = pre.executeUpdate();
			if (result == 1) return true;
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					e.printStackTrace();
				}
			}
		}
		return false;
	}
}