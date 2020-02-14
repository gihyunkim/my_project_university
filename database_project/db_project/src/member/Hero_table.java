package member;

public class Hero_table {
	private String id;
	private String pwd;
	private String name;
	private int age;
	private String hometown;
	private String species;
	private int attack_p;//attack power
	private int defend_p;//defense power
	private int hp;	//health point
	private int mp;	//mana point ¸¶·Â
	private int str;	//strength
	private int intel;//intelligence
	private double total_attack;
	private double total_defense;
	private double total_hp;
	private double total_mp;
	private double total_str;
	private double total_int;
	
	public double getTotal_attack() {
		return total_attack;
	}
	public void setTotal_attack(double total_attack) {
		this.total_attack = total_attack;
	}
	public double getTotal_defense() {
		return total_defense;
	}
	public void setTotal_defense(double total_defense) {
		this.total_defense = total_defense;
	}
	public double getTotal_hp() {
		return total_hp;
	}
	public void setTotal_hp(double total_hp) {
		this.total_hp = total_hp;
	}
	public double getTotal_mp() {
		return total_mp;
	}
	public void setTotal_mp(double total_mp) {
		this.total_mp = total_mp;
	}
	public double getTotal_str() {
		return total_str;
	}
	public void setTotal_str(double total_str) {
		this.total_str = total_str;
	}
	public double getTotal_int() {
		return total_int;
	}
	public void setTotal_int(double total_int) {
		this.total_int = total_int;
	}
	public String getSpecies() {
		return species;
	}
	public void setSpecies(String species) {
		this.species = species;
	}
	public int getAttack_p() {
		return attack_p;
	}
	public void setAttack_p(int attack_p) {
		this.attack_p = attack_p;
	}
	public int getDefend_p() {
		return defend_p;
	}
	public void setDefend_p(int defend_p) {
		this.defend_p = defend_p;
	}
	public int getHp() {
		return hp;
	}
	public void setHp(int hp) {
		this.hp = hp;
	}
	public int getMp() {
		return mp;
	}
	public void setMp(int mp) {
		this.mp = mp;
	}
	public int getStr() {
		return str;
	}
	public void setStr(int str) {
		this.str = str;
	}
	public int getIntel() {
		return intel;
	}
	public void setIntel(int intel) {
		this.intel = intel;
	}
	
	
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getPwd() {
		return pwd;
	}
	public void setPwd(String pwd) {
		this.pwd = pwd;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
	public String getHometown() {
		return hometown;
	}
	public void setHometown(String hometown) {
		this.hometown = hometown;
	}
	
}
