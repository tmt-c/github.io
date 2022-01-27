package db;
import java.io.IOException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
@WebServlet("/BookServlet")
public class BookServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	public BookServlet() {
		super();
	}
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws
	ServletException, IOException {
		request.setCharacterEncoding("UTF-8");
		String item = request.getParameter("item"); // 並び替えの項目
		String order = request.getParameter("order"); // asc:昇順 desc:降順

		String search_d = request.getParameter("search_d");
		String search_g = request.getParameter("search_g");

		String submit = request.getParameter("submit"); //並び替え 登録 削除

		//登録項目
		String newtitle = request.getParameter("newtitle");
		String newname = request.getParameter("newname");
		String newdate = request.getParameter("newdate");
		String newgenre = request.getParameter("newgenre");
		String newprice = request.getParameter("newprice");
		String newpoint = request.getParameter("newpoint");
		String newdenshi = request.getParameter("newdenshi");;
		String deleteid = request.getParameter("deleteid"); // 削除するID

		//ボタン処理
		if (submit != null) {
			if (submit.equals("並び替え")) {
			} else if (submit.equals("検索")) {
			} else if (submit.equals("登録")) {
				insert(newtitle, newname, newdate, newgenre, newprice, newpoint, newdenshi);
			} else if (submit.equals("削除")) {
				delete(deleteid);
			}
		}
		selectAll(request, response, item, order, search_d, search_g);
		RequestDispatcher dispatcher = request.getRequestDispatcher("/book.jsp");
		dispatcher.forward(request, response);
	}

/** サーブレットがPOSTメソッドで実行された場合でもdoGet()で処理 */
protected void doPost(HttpServletRequest request, HttpServletResponse response) throws
ServletException, IOException {
	doGet(request, response);
}
/** 全表示・DAO呼出 */
void selectAll(HttpServletRequest request, HttpServletResponse response, String item, String order, String search_d, String search_g)
throws ServletException {
	BookDAO bookDAO = new BookDAO();
	List<Book> list = bookDAO.findAll(item, order, search_d, search_g);
	request.setAttribute("list", list);
}
/** 追加・DAO呼出 */
void insert(String newtitle, String newname, String newdate, String newgenre, String newprice, String newpoint, String newdenshi ) {
	try {
		int da = Integer.parseInt(newdate);
		int pr = Integer.parseInt(newprice);
		int pt = Integer.parseInt(newpoint);
		BookDAO bookDAO = new BookDAO();
		boolean success = bookDAO.insert(newtitle, newname, da, newgenre, pr, pt, newdenshi);
		System.out.println(success);
	} catch (NumberFormatException e) {
			System.out.println("不正な値です…"+e.getMessage());
		}
	}
/** 削除・DAO呼出 */
void delete(String deleteid) {
	try {
		int id = Integer.parseInt(deleteid);
		BookDAO bookDAO = new BookDAO();
		boolean success = bookDAO.delete(id);
		System.out.println(success);
	} catch (NumberFormatException e) {
			 System.out.println("不正なIDです！"+e.getMessage());
		}
	}
}