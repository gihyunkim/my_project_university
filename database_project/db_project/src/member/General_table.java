package member;

public class General_table {
	private String general_name;
	private int age;
	private double army_attack_comp;
	private double army_defense_comp;
	private double army_moral_comp;	//사기 보정치
	private double army_loco_comp;	//이동력 보정치
	private String rival;	//천적
	
	
	public String getGeneral_name() {
		return general_name;
	}
	public void setGeneral_name(String general_name) {
		this.general_name = general_name;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
	public double getArmy_attack_comp() {
		return army_attack_comp;
	}
	public void setArmy_attack_comp(double army_attack_comp) {
		this.army_attack_comp = army_attack_comp;
	}
	public double getArmy_defense_comp() {
		return army_defense_comp;
	}
	public void setArmy_defense_comp(double army_defense_comp) {
		this.army_defense_comp = army_defense_comp;
	}
	public double getArmy_moral_comp() {
		return army_moral_comp;
	}
	public void setArmy_moral_comp(double army_moral_comp) {
		this.army_moral_comp = army_moral_comp;
	}
	public double getArmy_loco_comp() {
		return army_loco_comp;
	}
	public void setArmy_loco_comp(double army_loco_comp) {
		this.army_loco_comp = army_loco_comp;
	}
	public String getRival() {
		return rival;
	}
	public void setRival(String rival) {
		this.rival = rival;
	}
}
