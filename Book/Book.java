package db;

/** テーブルのデータを保持するクラス */
public class Book {
	private int id;
	private String title;
	private String name;
	private int date;
	private String genre;
	private int price;
	private int point;
	private String denshi;

	/** コンストラクタ */
	public Book(int id, String title, String name, int date, String genre, int price, int point, String denshi) {
	this.id = id;
	this.title = title;
	this.name = name;
	this.date = date;
	this.genre = genre;
	this.price = price;
	this.point = point;
	this.denshi = denshi;
	}
	public int getId() {return id;}
	public String getTitle() {return title;}
	public String getName() {return name;}
	public int getDate() {return date;}
	public String getGenre() {return genre;}
	public int getPrice() {return price;}
	public int getPoint() {return point;}
	public String getDenshi() {return denshi;}
}