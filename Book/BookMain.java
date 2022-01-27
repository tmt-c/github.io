package db;

import java.util.List;

public class BookMain {
	/** 追加 */
	void insert(String title, String name, int date,
			String genre, int price, int point, String denshi) {
		BookDAO bookDAO = new BookDAO();
		boolean success = bookDAO.insert(title, name, date, genre, price, point, denshi);
		System.out.println(success);
		}
	void delete(int id) {
			BookDAO bookDAO = new BookDAO();
			boolean success = bookDAO.delete(id);
			System.out.println(success);
		}
	void allBook() {
		BookDAO bookDAO = new BookDAO();
		List<Book> list = bookDAO.findAll(null, null, null, null);
		for (Book p: list) {
			int id = p.getId();
			String title = p.getTitle();
			String name = p.getName();
			int date = p.getDate();
			String genre = p.getGenre();
			int price = p.getPrice();
			int point = p.getPoint();
			String denshi = p.getDenshi();
			System.out.printf("%3d %-10s %-10s %3d %-10s %-3s %-3s %-3s\n",
					id, title, name, date, genre, price, point, denshi);
		}
	}
	public static void main(String args[]) {
		BookMain main = new BookMain();
		//main.insert(6, 12206, 2021, 6, 23, 13, 54, 00);
		//main.delete(7);
		main.allBook();
	}
}