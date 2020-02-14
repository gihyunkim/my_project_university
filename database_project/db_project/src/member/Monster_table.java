package member;

public class Monster_table {
	private String army_name;
	private int num_monster;
	private int total_defense;
	private int total_attack;
	private int locomotive;	//이동력
	private int moral; //사기
	private double army_total_attack;
	private double army_total_defense;
	private double army_total_loco;
	private double army_total_moral;
	
	public double getArmy_total_attack() {
		return army_total_attack;
	}
	public void setArmy_total_attack(double army_total_attack) {
		this.army_total_attack = army_total_attack;
	}
	public double getArmy_total_defense() {
		return army_total_defense;
	}
	public void setArmy_total_defense(double army_total_defense) {
		this.army_total_defense = army_total_defense;
	}
	public double getArmy_total_loco() {
		return army_total_loco;
	}
	public void setArmy_total_loco(double army_total_loco) {
		this.army_total_loco = army_total_loco;
	}
	public double getArmy_total_moral() {
		return army_total_moral;
	}
	public void setArmy_total_moral(double army_total_moral) {
		this.army_total_moral = army_total_moral;
	}
	public String getArmy_name() {
		return army_name;
	}
	public void setArmy_name(String army_name) {
		this.army_name = army_name;
	}
	public int getNum_monster() {
		return num_monster;
	}
	public void setNum_monster(int num_monster) {
		this.num_monster = num_monster;
	}
	public int getTotal_defense() {
		return total_defense;
	}
	public void setTotal_defense(int total_defense) {
		this.total_defense = total_defense;
	}
	public int getTotal_attack() {
		return total_attack;
	}
	public void setTotal_attack(int total_attack) {
		this.total_attack = total_attack;
	}
	public int getLocomotive() {
		return locomotive;
	}
	public void setLocomotive(int locomotive) {
		this.locomotive = locomotive;
	}
	public int getMoral() {
		return moral;
	}
	public void setMoral(int moral) {
		this.moral = moral;
	}
	
}
