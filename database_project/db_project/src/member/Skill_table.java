package member;

public class Skill_table {
	private String skill_id;
	private int hp_up;
	private int mp_up;
	private String hero_id;
	
	public String getSkill_id() {
		return skill_id;
	}
	public void setSkill_id(String skill_id) {
		this.skill_id = skill_id;
	}
	public int getHp_up() {
		return hp_up;
	}
	public void setHp_up(int hp_up) {
		this.hp_up = hp_up;
	}
	public int getMp_up() {
		return mp_up;
	}
	public void setMp_up(int mp_up) {
		this.mp_up = mp_up;
	}
	public String getHero_id() {
		return hero_id;
	}
	public void setHero_id(String hero_id) {
		this.hero_id = hero_id;
	}
}
