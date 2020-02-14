package member;

public class Item_table {
	private String item_id;
	private String type;
	private int attack_p_up;
	private int defend_p_up;
	private int str_up;
	private int int_up;
	private String hero_id;
	
	public String getItem_id() {
		return item_id;
	}
	public void setItem_id(String item_id) {
		this.item_id = item_id;
	}
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public int getAttack_p_up() {
		return attack_p_up;
	}
	public void setAttack_p_up(int attack_p_up) {
		this.attack_p_up = attack_p_up;
	}
	public int getDefend_p_up() {
		return defend_p_up;
	}
	public void setDefend_p_up(int defend_p_up) {
		this.defend_p_up = defend_p_up;
	}
	public int getStr_up() {
		return str_up;
	}
	public void setStr_up(int str_up) {
		this.str_up = str_up;
	}
	public int getInt_up() {
		return int_up;
	}
	public void setInt_up(int int_up) {
		this.int_up = int_up;
	}
	public String getHero_id() {
		return hero_id;
	}
	public void setHero_id(String hero_id) {
		this.hero_id = hero_id;
	};
}
