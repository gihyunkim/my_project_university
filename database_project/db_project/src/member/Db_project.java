package member;
import java.security.MessageDigest;
import java.sql.*;

import com.sun.org.apache.xerces.internal.util.SynchronizedSymbolTable;


public class Db_project {
	
	private Connection conn;
	private Statement stmt;
	private ResultSet rs;
	private PreparedStatement pstmt;
	private PreparedStatement pstmt1;
	private PreparedStatement pstmt2;
	private PreparedStatement pstmt3;
	private PreparedStatement pstmt4;
	private PreparedStatement pstmt5;
	
	Db_project(){
			try{
				//register driver
				Class.forName("oracle.jdbc.driver.OracleDriver");
			}catch(ClassNotFoundException e){
				e.printStackTrace();
			}
	}
	
	private static Db_project instance;
	
	public static Db_project getInstance(){
		if(instance==null){
			synchronized(Db_project.class){
				instance = new Db_project();
			}
		}
		return instance;
	}
		
	public void getConnection(){
		try{
			//connection
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:orcl", "system", "qlalfqjsgh");
		}catch(SQLException e){
			e.printStackTrace();
		}
	}
	
	public String login(String id, String pwd){
		String name=null;
		getConnection();
		String sql = "select * from member where id=? and pwd=?";
		
		try {
			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, id);
			pstmt.setString(2, pwd);
			rs = pstmt.executeQuery();
			if(rs.next()){
				name=rs.getString("name");
						
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
			// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return name;
	}
	
	public void writeHeroData(Hero_table hr){
		getConnection();
		String sql = "insert into hero values(?,?,?,?,?)";
		
	}
	
	//--------------------------정보 검색용 메소드--------------------------//
	public String[] getAdminTable(String id) {
		getConnection();
		String admin[] = new String [100];
		int i=0;
		String sql = "select adminid from administrator where adminid like ?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "%"+id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				admin[i]=rs.getString("adminid");
				i++;
			}
		
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return admin;
	}
	
	public int getAdminCnt(String id) {	//용사 수 카운트
		getConnection();
		int total_cnt=0;
		String sql = "select count(adminid) from (select adminid from administrator where adminid like ?)";
		try {

			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, "%"+id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				total_cnt=rs.getInt(1);
			}
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return total_cnt;
	}
	
	
	public String[] getHeroTable(String hero_id) {
		getConnection();
		String heroes[] = new String [1000];
		int i=0;
		String sql = "select hero_id from heroes where hero_id like ?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "%"+hero_id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				heroes[i]=rs.getString("hero_id");
				i++;
			}
		
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return heroes;
	}
	
	public int getHeroCnt(String hero_id) {	//용사 수 카운트
		getConnection();
		int total_cnt=0;
		String sql = "select count(hero_id) from (select hero_id from heroes where hero_id like ?)";
		try {

			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, "%"+hero_id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				total_cnt=rs.getInt(1);
			}
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return total_cnt;
	}
	
	public String[] getItemTable(String item_id) {	//get searched item list
		getConnection();
		String items[] = new String [1000];
		int i=0;
		String sql = "select item_id from item where item_id like ?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "%"+item_id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				items[i]=rs.getString("item_id");
				i++;
			}
		
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return items;
	}
	
	public int getItemCnt(String item_id) {	//count searched item
		getConnection();
		int total_cnt=0;
		String sql = "select count(item_id) from (select item_id from item where item_id like ?)";
		try {

			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, "%"+item_id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				total_cnt=rs.getInt(1);
			}
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return total_cnt;
	}
	
	public String[] getSkillTable(String skill_id) {	//get searched skill list
		getConnection();
		String skills[] = new String [1000];
		int i=0;
		String sql = "select skill_id from skill where skill_id like ?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "%"+skill_id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				skills[i]=rs.getString("skill_id");
				i++;
			}
		
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return skills;
	}
	
	public int getSkillCnt(String skill_id) {	//count searched skill
		getConnection();
		int total_cnt=0;
		String sql = "select count(skill_id) from (select skill_id from skill where skill_id like ?)";
		try {

			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, "%"+skill_id+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				total_cnt=rs.getInt(1);
			}
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return total_cnt;
	}
	
	public String[] getSpeciesTable(String species_name) {	//get searched species list
		getConnection();
		String species[] = new String [1000];
		int i=0;
		String sql = "select species_name from species where species_name like ?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "%"+species_name+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				species[i]=rs.getString("species_name");
				i++;
			}
		
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return species;
	}
	
	public int getSpeciesCnt(String species_name) {	//count searched species
		getConnection();
		int total_cnt=0;
		String sql = "select count(species_name) from (select species_name"
				+ " from species where species_name like ?)";
		try {

			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, "%"+species_name+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				total_cnt=rs.getInt(1);
			}
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return total_cnt;
	}
	
	
	public String[] getMonstersTable(String army_name) {	//get searched armies list
		getConnection();
		String monsters[] = new String [1000];
		int i=0;
		String sql = "select army_name from monster "
				+ "where army_name like ?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "%"+army_name+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				monsters[i]=rs.getString("army_name");
				i++;
			}
		
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return monsters;
	}
	
	public int getMonstersCnt(String army_name) {	//count searched armies
		getConnection();
		int total_cnt=0;
		String sql = "select count(army_name) from (select army_name"
				+ " from monster where army_name like ?)";
		try {

			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, "%"+army_name+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				total_cnt=rs.getInt(1);
			}
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return total_cnt;
	}
	
	public String[] getGeneralsTable(String general_name) {	//get searched armies list
		getConnection();
		String generals[] = new String [1000];
		int i=0;
		String sql = "select general_name from general "
				+ "where general_name like ?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, "%"+general_name+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				generals[i]=rs.getString("general_name");
				i++;
			}
		
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return generals;
	}
	
	public int getGeneralsCnt(String general_name) {	//count searched armies
		getConnection();
		int total_cnt=0;
		String sql = "select count(general_name) from (select general_name"
				+ " from general where general_name like ?)";
		try {

			pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, "%"+general_name+"%");
			rs = pstmt.executeQuery();
			
			while(rs.next()) {	
				total_cnt=rs.getInt(1);
			}
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return total_cnt;
	}
	
	
	//-------------상세정보용--------------------------------//
	
	public String[] getAdminInfo(String id) {
		getConnection();
		String admin [] = new String [2];
		String sql = "select * from administrator where adminid=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, id);
			rs= pstmt.executeQuery();
			while(rs.next()) {
				admin[0] = rs.getString("adminid");
				admin[1] = rs.getString("pwd");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return admin;
	}
	
	public Hero_table getHeroInfo(String hero_id) {
		getConnection();
		Hero_table ht = new Hero_table();
		String sql = "select * from heroes where hero_id=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, hero_id);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				ht.setId(rs.getString("hero_id"));
				ht.setPwd(rs.getString("hero_pwd"));
				ht.setName(rs.getString("hero_name"));
				ht.setAge(rs.getInt("hero_age"));
				ht.setHometown(rs.getString("born"));
				ht.setSpecies(rs.getString("species"));
				ht.setAttack_p(rs.getInt("attack_p"));
				ht.setDefend_p(rs.getInt("defend_p"));
				ht.setHp(rs.getInt("hp"));
				ht.setMp(rs.getInt("mp"));
				ht.setStr(rs.getInt("str"));
				ht.setIntel(rs.getInt("int"));
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return ht;
	}
	
	public Hero_table applied_comp(String hero_id) {
		
		Hero_table ht = new Hero_table();
		getConnection();
		String species="";
		int attack_p=0, defend_p=0,hp=0,mp=0, str=0, intel=0;	//heroes status
		int attack_p_up=0, defend_p_up=0, str_up=0, int_up=0;	//stat up from skill
		int hp_up=0, mp_up=0;	//stat up from item
		double attack_p_comp=0, defend_p_comp=0, hp_comp=0, mp_comp=0, str_comp=0, int_comp=0; //stat compensation from species
		double total_attack=0, total_defense=0, total_hp=0, total_mp=0, total_str=0, total_int=0;
		
		String sql1 = "select species, attack_p, defend_p, hp, mp, str, int"
				+ " from heroes where hero_id=?";
		String sql2 = "select attack_p_up, defend_p_up, str_up, int_up"
				+ " from item  where hero_id =?";
		String sql3 = "select hp_up, mp_up"
				+ " from skill where hero_id=?";
		String sql4 = "select attack_p_comp, defend_p_comp, hp_comp, mp_comp,"
				+ "str_comp, int_comp"
				+ " from species"
				+ " where species_name=?";
		try {
			pstmt = conn.prepareStatement(sql1);
			pstmt.setString(1, hero_id);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				species = rs.getString("species");
				attack_p = rs.getInt("attack_p");
				defend_p = rs.getInt("defend_p");
				hp = rs.getInt("hp");
				mp = rs.getInt("mp");
				str = rs.getInt("str");
				intel = rs.getInt("int");
			}
			pstmt1 = conn.prepareStatement(sql2);
			pstmt1.setString(1, hero_id);
			rs = pstmt1.executeQuery();
			while(rs.next()) {
				attack_p_up = rs.getInt("attack_p_up");
				defend_p_up = rs.getInt("defend_p_up");
				str_up = rs.getInt("str_up");
				int_up = rs.getInt("int_up");
			}
			pstmt2 = conn.prepareStatement(sql3);
			pstmt2.setString(1, hero_id);
			rs = pstmt2.executeQuery();
			while(rs.next()) {
				hp_up = rs.getInt("hp_up");
				mp_up = rs.getInt("mp_up");
			}
			pstmt3 = conn.prepareStatement(sql4);
			pstmt3.setString(1, species);
			rs = pstmt3.executeQuery();
			while(rs.next()) {
				attack_p_comp = rs.getDouble("attack_p_comp");
				defend_p_comp = rs.getDouble("defend_p_comp");
				str_comp = rs.getDouble("str_comp");
				hp_comp = rs.getDouble("hp_comp");
				mp_comp = rs.getDouble("mp_comp");
				int_comp = rs.getDouble("int_comp");
			}
			total_attack = (attack_p + attack_p_up)*attack_p_comp;
			total_defense = (defend_p + defend_p_up)*defend_p_comp;
			total_hp = (hp+hp_up)*hp_comp;
			total_mp = (mp+mp_up)*mp_comp;
			total_str = (str+str_up)*str_comp;
			total_int = (intel+int_up)*int_comp;
			
			total_attack = Math.round(total_attack*1000.0)/1000.0;
			total_defense = Math.round(total_defense*1000.0)/1000.0;
			total_hp = Math.round(total_hp*1000.0)/1000.0;
			total_mp = Math.round(total_mp*1000.0)/1000.0;
			total_str = Math.round(total_str*1000.0)/1000.0;
			total_int = Math.round(total_int*1000.0)/1000.0;
			
			
			ht.setTotal_attack(total_attack);
			ht.setTotal_defense(total_defense);
			ht.setTotal_hp(total_hp);
			ht.setTotal_int(total_int);
			ht.setTotal_mp(total_mp);
			ht.setTotal_str(total_str);
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return ht;
		
	}
	
	
public Monster_table army_applied_comp(String army_name) {
		
		Monster_table mt = new Monster_table();
		getConnection();
		String general="";
		int i=0;
		int total_defense=0, total_attack=0, locomotive=0, moral=0;
		double army_attack_comp=0, army_defense_comp=0, army_moral_comp=0, army_loco_comp=0;
		double army_total_attack=0, army_total_defense=0, army_total_moral=0, army_total_loco=0;
		String sql="select total_defense, total_attack, locomotive, moral"
				+ " from monster where army_name=?";
		String sql1 = "select general_name from command where army_name=?";
		String sql2 ="select army_attack_comp, army_defense_comp, army_moral_comp,"
				+ "army_loco_comp from general where general_name=?";

		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, army_name);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				total_defense = rs.getInt("total_defense");
				total_attack = rs.getInt("total_attack");
				locomotive = rs.getInt("locomotive");
				moral = rs.getInt("moral");	
			}
			
			pstmt1 = conn.prepareStatement(sql1);
			pstmt1.setString(1, army_name);
			rs = pstmt1.executeQuery();
			while(rs.next()) {
				general = rs.getString("general_name");
				i++;
			}
			
			pstmt2=conn.prepareStatement(sql2);
			pstmt2.setString(1,general );
			rs = pstmt2.executeQuery();
			while(rs.next()) {
				army_attack_comp = rs.getDouble("army_attack_comp");
				army_defense_comp = rs.getDouble("army_defense_comp");
				army_moral_comp = rs.getDouble("army_moral_comp");
				army_loco_comp = rs.getDouble("army_loco_comp");
			}
			
			army_total_attack = total_attack*army_attack_comp;
			army_total_defense = total_defense*army_defense_comp;
			army_total_moral = moral*army_moral_comp;
			army_total_loco = locomotive*army_loco_comp;
			mt.setArmy_total_attack(army_total_attack);
			mt.setArmy_total_defense(army_total_defense);
			mt.setArmy_total_loco(army_total_loco);
			mt.setArmy_total_moral(army_total_moral);
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return mt;
		
	}
	public Skill_table getSkillInfo(String skill_id) {
		getConnection();
		Skill_table st = new Skill_table();
		String sql = "select * from skill where skill_id=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, skill_id);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				st.setSkill_id(rs.getString("skill_id"));
				st.setHp_up(rs.getInt("hp_up"));
				st.setMp_up(rs.getInt("mp_up"));	
				st.setHero_id(rs.getString("hero_id"));
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return st;
	}
	
	public Species_table getSpeciesInfo(String species_name) {
		getConnection();
		Species_table spt = new Species_table();
		String sql = "select * from species where species_name=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, species_name);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				spt.setSpecies_name(rs.getString("species_name"));
				spt.setAttack_p_comp(rs.getDouble("attack_p_comp"));
				spt.setDefend_p_comp(rs.getDouble("defend_p_comp"));
				spt.setHp_comp(rs.getDouble("hp_comp"));
				spt.setMp_comp(rs.getDouble("mp_comp"));
				spt.setStr_comp(rs.getDouble("str_comp"));
				spt.setInt_comp(rs.getDouble("int_comp"));
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return spt;
	}
	
	public Item_table getItemInfo(String item_id) {
		getConnection();
		Item_table it = new Item_table();
		String sql = "select * from item where item_id=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, item_id);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				it.setItem_id(rs.getString("item_id"));
				it.setType(rs.getString("type"));
				it.setAttack_p_up(rs.getInt("attack_p_up"));
				it.setDefend_p_up(rs.getInt("defend_p_up"));
				it.setStr_up(rs.getInt("str_up"));
				it.setInt_up(rs.getInt("int_up"));
				it.setHero_id(rs.getString("hero_id"));
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return it;
	}
	
	public Monster_table getMonsterInfo(String army_name) {
		getConnection();
		Monster_table mt = new Monster_table();
		String sql = "select * from monster where army_name=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, army_name);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				mt.setArmy_name(rs.getString("army_name"));
				mt.setNum_monster(rs.getInt("num_monster"));
				mt.setTotal_attack(rs.getInt("total_attack"));
				mt.setTotal_defense(rs.getInt("total_defense"));
				mt.setLocomotive(rs.getInt("locomotive"));
				mt.setMoral(rs.getInt("moral"));
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return mt;
	}
	
	
	public General_table getGeneralInfo(String general_name) {
		getConnection();
		General_table gt = new General_table();
		String sql = "select * from general where general_name=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, general_name);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				gt.setGeneral_name(rs.getString("general_name"));
				gt.setAge(rs.getInt("age"));
				gt.setArmy_attack_comp(rs.getDouble("army_attack_comp"));
				gt.setArmy_defense_comp(rs.getDouble("army_defense_comp"));
				gt.setArmy_moral_comp(rs.getDouble("army_moral_comp"));
				gt.setArmy_loco_comp(rs.getDouble("army_loco_comp"));
				gt.setRival(rs.getString("rival"));
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return gt;
	}
	
	
	
	public String check_login(String id, String pwd) {
		getConnection();
		String aid= null;	//체크용
		String sql = "select * from administrator where adminID=? and pwd=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, id);
			pstmt.setString(2, pwd);
			rs = pstmt.executeQuery();
			
			while(rs.next()) {
				aid = rs.getString("adminID");
			}

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return aid;
	}
	
	
	
	//-----------------등록 부분------------------------------------------------//
	public int RegisterHero(Hero_table ht) {//실질적으로 데이터베이스에 새로운 히어로 데이터 저장
		getConnection();
		int check=0;
		String sql = "insert into heroes values(?,?,?,?,?,?,?,?,?,?,?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, ht.getId());
			pstmt.setString(2, ht.getPwd());
			pstmt.setString(3, ht.getName());
			pstmt.setInt(4, ht.getAge());
			pstmt.setString(5, ht.getHometown());
			pstmt.setString(6, ht.getSpecies());
			pstmt.setInt(7, ht.getAttack_p());
			pstmt.setInt(8, ht.getDefend_p());
			pstmt.setInt(9, ht.getHp());
			pstmt.setInt(10, ht.getMp());
			pstmt.setInt(11, ht.getStr());
			pstmt.setInt(12, ht.getIntel());
			
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public String[] getAllSpecies() {	//모든 종족 불러오기 
		getConnection();
		String species [] = new String[100];
		String sql = "select species_name from species";
		int i =0;
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				species[i] = rs.getString("species_name");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return species;
	}
	
	public int CntAllSpecies() {	//모든 종족 카운트
		getConnection();
		int total_count=0;
		String sql = "select count(species_name) from species";
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_count = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_count;
	}
	
	public String[] getAllGeneral() {	//모든 마물 장군 불러오기 
		getConnection();
		String generals [] = new String[100];
		String sql = "select general_name from general";
		int i =0;
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				generals[i] = rs.getString("general_name");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return generals;
	}
	
	public int CntAllGeneral() {	//모든 마물 장군 카운트
		getConnection();
		int total_count=0;
		String sql = "select count(general_name) from general";
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_count = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_count;
	}
	
	public String[] getAllMonster() {	//모든 마물 군단 불러오기 
		getConnection();
		String monsters [] = new String[100];
		String sql = "select army_name from monster";
		int i =0;
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				monsters[i] = rs.getString("army_name");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return monsters;
	}
	
	public int CntAllMonsters() {	//모든 마물 군단 카운트
		getConnection();
		int total_count=0;
		String sql = "select count(army_name) from monster";
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_count = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_count;
	}
	
	public int CntCommand() {	// 지휘체계 카운트
		getConnection();
		int total_count=0;
		String sql = "select count(army_name) from command";
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_count = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_count;
	}
	
	public int CntTotalNumOfMonsters() {
		getConnection();
		int total_monster=0;
		String sql="select sum(num_monster) from monster";
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_monster = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_monster;
		
	}
	public String[] getAllHeroes() {	//모든 용사들 불러오기 
		getConnection();
		String heroes [] = new String[100];
		String sql = "select hero_id from heroes";
		int i =0;
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				heroes[i] = rs.getString("hero_id");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return heroes;
	}
	
	public int CntAllHeroes() {	//모든 용사 카운트
		getConnection();
		int total_count=0;
		String sql = "select count(hero_id) from heroes";
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_count = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_count;
	}
	
	public int RegisterSkill(Skill_table st) {//실질적으로 데이터베이스에 새로운 스킬 데이터 저장
		getConnection();
		int check=0;
		String sql = "insert into skill values(?,?,?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, st.getSkill_id());
			pstmt.setInt(2, st.getHp_up());
			pstmt.setInt(3, st.getMp_up());
			pstmt.setString(4, st.getHero_id());
			
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public String[] getSkills() {	//선택 가능한 스킬 불러오기 
		getConnection();
		String skills [] = new String[100];
		String sql = "select skill_id from skill where hero_id is null";
		int i =0;
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				skills[i] = rs.getString("skill_id");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return skills;
	}
	
	public int CntSkills() {	//선택가능한  스킬 카운트 
		getConnection();
		int total_count=0;
		String sql = "select count(skill_id) from skill where hero_id is null";
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_count = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_count;
	}
	
	public String[] getHeroes() {	//부여 가능한 영웅 불러오기 
		getConnection();
		String heroes [] = new String[100];
		String sql = "select hero_id from heroes where hero_id not in "
				+ "(select hero_id from skill where hero_id is not null)";
		int i =0;
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				heroes[i] = rs.getString("hero_id");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return heroes;
	}
	
	public int CntHeroes() {	//선택가능한  용사 카운트 
		getConnection();
		int total_count=0;
		String sql = "select count(hero_id) from "
				+ "(select hero_id from heroes where hero_id not in "
				+ "(select hero_id from skill where hero_id is not null))";
		
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				total_count = rs.getInt(1);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return total_count;
	}
	
	public int RegisterItem(Item_table it) {//실질적으로 데이터베이스에 새로운 아이템 데이터 저장
		getConnection();
		int check=0;
		String sql = "insert into item values(?,?,?,?,?,?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, it.getItem_id());
			pstmt.setString(2, it.getType());
			pstmt.setInt(3, it.getAttack_p_up());
			pstmt.setInt(4, it.getDefend_p_up());
			pstmt.setInt(5, it.getStr_up());
			pstmt.setInt(6, it.getInt_up());
			pstmt.setString(7, it.getHero_id());
			
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int RegisterSpecies(Species_table spt) {//실질적으로 데이터베이스에 새로운 아이템 데이터 저장
		getConnection();
		int check=0;
		String sql = "insert into species values(?,?,?,?,?,?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, spt.getSpecies_name());
			pstmt.setDouble(2, spt.getAttack_p_comp());
			pstmt.setDouble(3, spt.getDefend_p_comp());
			pstmt.setDouble(4, spt.getHp_comp());
			pstmt.setDouble(5, spt.getMp_comp());
			pstmt.setDouble(6, spt.getStr_comp());
			pstmt.setDouble(7, spt.getInt_comp());
			
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int RegisterMonster(Monster_table mt) {//실질적으로 데이터베이스에 새로운 마물군단  데이터 저장
		getConnection();
		int check=0;
		String sql = "insert into monster values(?,?,?,?,?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, mt.getArmy_name());
			pstmt.setInt(2, mt.getNum_monster());
			pstmt.setInt(3, mt.getTotal_defense());
			pstmt.setInt(4, mt.getTotal_attack());
			pstmt.setInt(5, mt.getLocomotive());
			pstmt.setInt(6, mt.getMoral());
			
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int setCommandMonster(String new_army, String general_name) {
		getConnection();
		String sql = "insert into command values(?,?)";
		int check =0;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, new_army);
			pstmt.setString(2, general_name);
			check = pstmt.executeUpdate();
			
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
		
		
	}
	
	public int RegisterGeneral(General_table gt) {//실질적으로 데이터베이스에 새로운 마물장군 데이터 저장
		getConnection();
		int check=0;
		String sql = "insert into general values(?,?,?,?,?,?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, gt.getGeneral_name());
			pstmt.setInt(2, gt.getAge());
			pstmt.setDouble(3, gt.getArmy_attack_comp());
			pstmt.setDouble(4, gt.getArmy_defense_comp());
			pstmt.setDouble(5, gt.getArmy_moral_comp());
			pstmt.setString(6, gt.getRival());
			pstmt.setDouble(7, gt.getArmy_loco_comp());	
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int RegisterAdmin(String id, String pwd) {//실질적으로 데이터베이스에 새로운 관리자 데이터 저장
		getConnection();
		int check=0;
		String sql = "insert into administrator values(?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, id);
			pstmt.setString(2, pwd);
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public String encryptPwd(String pwd) throws Exception {
		MessageDigest md = MessageDigest.getInstance("SHA-256");
		byte[] mdResult = md.digest(pwd.getBytes("UTF-8"));
		sun.misc.BASE64Encoder encoder = new sun.misc.BASE64Encoder();
		String str = encoder.encode(mdResult);
		return str;
	}
	
	
	//---------------수정을 위한 메소드---------------------------------///
	public int modifyAdmin(String old_id, String id, String pwd) {//관리자 정보 수정
		getConnection();
		int check=0;
		String sql = "update administrator set adminid=?, pwd=? where adminid=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, id);
			pstmt.setString(2, pwd);
			pstmt.setString(3, old_id);
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int modifyHero(Hero_table ht) {//용사 정보 수정
		getConnection();
		int check=0;
		String sql = "update heroes set hero_pwd=?,hero_name=?,"
				+ "hero_age=?,born=?,species=?,attack_p=?,defend_p=?,hp=?,mp=?,"
				+ "str=?,int=? where hero_id=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, ht.getPwd());
			pstmt.setString(2, ht.getName());
			pstmt.setInt(3, ht.getAge());
			pstmt.setString(4, ht.getHometown());
			pstmt.setString(5, ht.getSpecies());
			pstmt.setInt(6, ht.getAttack_p());
			pstmt.setInt(7, ht.getDefend_p());
			pstmt.setInt(8, ht.getHp());
			pstmt.setInt(9, ht.getMp());
			pstmt.setInt(10, ht.getStr());
			pstmt.setInt(11, ht.getIntel());
			pstmt.setString(12, ht.getId());
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	/*public int modifyHero_id(Hero_table ht, String old_id) {//용사 정보를 수정
		getConnection();
		int check=0;
		String skill_id="";
		int hp_up=0;
		int mp_up=0;
		
		String item_id="";
		String type ="";
		int attack_p_up=0;
		int defend_p_up=0;
		int str_up=0;
		int int_up=0;
		String sql1 = "select skill_id, hp_up,mp_up from skill where hero_id=?";
		String sql2 = "select item_id,type,attack_p_up, defend_p_up, str_up, int_up from item where hero_id=?";
		String sql3 = "delete from heroes where hero_id=?";
		String sql4 = "insert into heroes values(?,?,?,?,?,?,?,?,?,?,?,?)";
		String sql5 = "insert into skill values(?,?,?,?)";
		String sql6 = "insert into item values(?,?,?,?,?,?,?)";
		try {
			pstmt = conn.prepareStatement(sql1);
			pstmt.setString(1, old_id);
			rs = pstmt.executeQuery();
			while(rs.next()) {	//hero_id가 가지고 있던 skill
				skill_id = rs.getString("skill_id");
				hp_up =rs.getInt("hp_up");
				mp_up=rs.getInt("mp_up");
			}
			pstmt1 = conn.prepareStatement(sql2);
			pstmt1.setString(1, old_id);
			rs = pstmt1.executeQuery();
			while(rs.next()) {	//hero_id가 가지고 있던 아이템
				item_id = rs.getString("item_id");
				type=rs.getString("type");
				attack_p_up=rs.getInt("attack_p_up");
				defend_p_up=rs.getInt("defend_p_up");
				str_up =rs.getInt("str_up");
				int_up =rs.getInt("int_up");
			}
			//hero_id삭제
			pstmt2 = conn.prepareStatement(sql3);
			pstmt2.setString(1, old_id);
			pstmt2.execute();
			
			//수정된 정보 입력
			pstmt3 = conn.prepareStatement(sql4);
			pstmt3.setString(1, ht.getId());
			pstmt3.setString(2, ht.getPwd());
			pstmt3.setString(3, ht.getName());
			pstmt3.setInt(4, ht.getAge());
			pstmt3.setString(5, ht.getHometown());
			pstmt3.setString(6, ht.getSpecies());
			pstmt3.setInt(7, ht.getAttack_p());
			pstmt3.setInt(8, ht.getDefend_p());
			pstmt3.setInt(9, ht.getHp());
			pstmt3.setInt(10, ht.getMp());
			pstmt3.setInt(11, ht.getStr());
			pstmt3.setInt(12, ht.getIntel());
			pstmt3.executeUpdate();
			
			//복구
			pstmt4 = conn.prepareStatement(sql5);
			pstmt4.setString(1, skill_id);
			pstmt4.setInt(2, hp_up);
			pstmt4.setInt(3, mp_up);
			pstmt4.setString(4, ht.getId());
			pstmt4.executeUpdate();
			
			pstmt5 = conn.prepareStatement(sql6);
			pstmt5.setString(1, item_id);
			pstmt5.setString(2, type);
			pstmt5.setInt(3, attack_p_up);
			pstmt5.setInt(4, defend_p_up);
			pstmt5.setInt(5, str_up);
			pstmt5.setInt(6, int_up);
			pstmt5.setString(7, ht.getId());
			pstmt5.executeUpdate();
			
		
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}*/
	
	public int modifySkill(Skill_table st, String old_skill) {//스킬 정보 수정
		getConnection();
		int check=0;
		String sql = "update skill set skill_id=?, hp_up=?, mp_up=?, hero_id=? "
				+ "where skill_id=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, st.getSkill_id());
			pstmt.setInt(2, st.getHp_up());
			pstmt.setInt(3, st.getMp_up());
			pstmt.setString(4, st.getHero_id());
			pstmt.setString(5, old_skill);
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int modifyItem(Item_table it, String old_item) {//아이템 정보 수정
		getConnection();
		int check=0;
		String sql = "update item set item_id=?, type=?,attack_p_up=?,"
				+ "defend_p_up=?, str_up=?, int_up=?, hero_id=? where item_id=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, it.getItem_id());
			pstmt.setString(2, it.getType());
			pstmt.setInt(3, it.getAttack_p_up());
			pstmt.setInt(4, it.getDefend_p_up());
			pstmt.setInt(5, it.getStr_up());
			pstmt.setInt(6,it.getInt_up());
			pstmt.setString(7, it.getHero_id());
			pstmt.setString(8, old_item);
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int modifySpecies(Species_table spt) {//종족 정보 수정
		getConnection();
		int check=0;
		String sql = "update species set attack_p_comp=?, defend_p_comp=?, "
				+ "hp_comp=?,mp_comp=?,str_comp=?, int_comp=? where species_name=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setDouble(1, spt.getAttack_p_comp());
			pstmt.setDouble(2, spt.getDefend_p_comp());
			pstmt.setDouble(3, spt.getHp_comp());
			pstmt.setDouble(4, spt.getMp_comp());
			pstmt.setDouble(5, spt.getStr_comp());
			pstmt.setDouble(6, spt.getInt_comp());
			pstmt.setString(7, spt.getSpecies_name());
			check = pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int modifyArmy(Monster_table mt, String general_name, int check2) {//군단 정보 수정
		getConnection();
		int check=0;
		String sql = "update monster set num_monster=?,total_defense=?, total_attack=?,"
				+ "locomotive=?, moral=? where army_name=?";
		String sql1 = "insert into set general_name=? where army_name=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, mt.getNum_monster());
			pstmt.setInt(2, mt.getTotal_defense());
			pstmt.setInt(3, mt.getTotal_attack());
			pstmt.setInt(4, mt.getLocomotive());
			pstmt.setInt(5, mt.getMoral());
			pstmt.setString(6, mt.getArmy_name());
			check = pstmt.executeUpdate();
			
			if(check2!=1) {
				pstmt = conn.prepareStatement(sql1);
				pstmt.setString(1, general_name);
				pstmt.setString(2, mt.getArmy_name());
				pstmt.executeUpdate();
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public int modifyGeneral(General_table gt, String army_name, int check2) {//장군 정보 수정
		getConnection();
		int check=0;
		String sql = "update general set age=?,army_attack_comp=?,army_defense_comp=?"
				+ ",army_moral_comp=?,rival=?,army_loco_comp=? where general_name=?";
		String sql1 = "insert into command values(?,?)";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, gt.getAge());
			pstmt.setDouble(2, gt.getArmy_attack_comp());
			pstmt.setDouble(3, gt.getArmy_defense_comp());
			pstmt.setDouble(4, gt.getArmy_moral_comp());
			pstmt.setString(5, gt.getRival());
			pstmt.setDouble(6, gt.getArmy_loco_comp());
			pstmt.setString(7, gt.getGeneral_name());
			check = pstmt.executeUpdate();
			if(check2!=1) {
				pstmt = conn.prepareStatement(sql1);
				pstmt.setString(1, army_name);
				pstmt.setString(2, gt.getGeneral_name());
				pstmt.executeUpdate();
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return check;
	}
	
	public String[] getCommandGeneral(String army_name) {
		getConnection();
		int i=0;
		String command_general[] = new String[100];
		String sql = "select general_name from command where army_name=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, army_name);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				command_general[i] = rs.getString("general_name");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return command_general;
		
	}
	
	public String[] getCommandArmy(String general_name) {
		getConnection();
		int i=0;
		String command_army[] = new String[100];
		String sql = "select army_name from command where general_name=?";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, general_name);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				command_army[i] = rs.getString("army_name");
				i++;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			try {
				rs.close();
				pstmt.close();
				conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		return command_army;
		
	}
	
	//-----------------------삭제용 메소드 ------------------------//
	
	
		public int delete_admin(String id) {
			getConnection();
			int check=0;
			String sql = "delete from administrator where adminid=?";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, id);
				check = pstmt.executeUpdate();
			
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			
			}
			return check;
		}
		public int delete_hero(String hero_id) {
			getConnection();
			int check=0;
			String sql = "delete from heroes where hero_id=?";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, hero_id);
				check = pstmt.executeUpdate();
				
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return check;
		}
		
		public int delete_skill(String skill_id) {
			getConnection();
			int check=0;
			String sql = "delete from skill where skill_id=?";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, skill_id);
				check = pstmt.executeUpdate();
				
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return check;
		}
		
		public int delete_item(String item_id) {
			getConnection();
			int check=0;
			String sql = "delete from item where item_id=?";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, item_id);
				check = pstmt.executeUpdate();
				
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return check;
		}
		
		public int delete_species(String species_name) {
			getConnection();
			int check=0;
			String sql = "delete from species where species_name=?";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, species_name);
				check = pstmt.executeUpdate();
				
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return check;
		}
		
		public int delete_army(String army_name) {
			getConnection();
			int check=0;
			String sql = "delete from monster where army_name=?";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, army_name);
				check = pstmt.executeUpdate();
				
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return check;
		}
		
		public int delete_general(String general_name) {
			getConnection();
			int check=0;
			String sql = "delete from general where general_name=?";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, general_name);
				check = pstmt.executeUpdate();
				
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return check;
		}
		
		//----------------- 통계 가져오기-------------------//
		
		public double[] totalHeroStatus() {
			String heroes[] = getAllHeroes();
			double status [] = new double [2];
			int count = CntAllHeroes();
			Hero_table ht [] = new Hero_table[1000];
			for(int i=0;i<count;i++) {//status[0] : 총 공격력, [1]:총 방어력
				ht[i] = applied_comp(heroes[i]);
				status[0]+=ht[i].getTotal_attack()+(3*ht[i].getTotal_str()+
				4*ht[i].getTotal_int()+2*ht[i].getTotal_mp());
				status[1] += ht[i].getTotal_hp()+3*ht[i].getTotal_defense();
			}
			//총 공격력 = 공격력 +(3*힘 + 4*지능 + 2*마력)
			//총 방어력 = 체력 +3*방어력
			return status;
		}
		
		public double[] totalArmyStatus() {
			String army[] = getAllMonster();
			double status [] = new double [2];
			int count = CntAllMonsters();
			Monster_table mt [] = new Monster_table[1000];
			for(int i=0;i<count;i++) {//status[0] : 총 공격력, [1]:총 방어력
				mt[i] = army_applied_comp(army[i]);
				status[0] += mt[i].getArmy_total_attack()+6*mt[i].getArmy_total_loco();
				status[1] += mt[i].getArmy_total_defense()+5*mt[i].getArmy_total_moral();
			}
			//총 공격력 = 공격력 +6*이동력;
			//총 방어력 = 방어력 +5*사기
			return status;
		}
		
		public String[] current_command_general() {
			String general[] = new String[100];
			getConnection();
			int i =0;
			String sql="select general_name from command";
			try {
				pstmt = conn.prepareStatement(sql);
				rs =pstmt.executeQuery();
				while(rs.next()) {
					general[i] = rs.getString("general_name");
					i++;
				}
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					rs.close();
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return general;
			
			
		}
		
		public String[] current_command_army() {
			String army[] = new String[100];
			getConnection();
			int i =0;
			String sql="select army_name from command";
			try {
				pstmt = conn.prepareStatement(sql);
				rs =pstmt.executeQuery();
				while(rs.next()) {
					army[i] = rs.getString("army_name");
					i++;
				}
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					rs.close();
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			return army;
			
			
		}
		
		public int[] current_species() {
			String species[] = getAllSpecies();
			int count = CntAllSpecies();
			int species_cnt [] = new int[100];

			getConnection();
			String sql = "select count(hero_id) from heroes "
					+ "where species=?";
			try {
				pstmt = conn.prepareStatement(sql);
				for(int i=0, j=0;i<count;i++,j++) {
					pstmt.setString(1, species[i]);
					rs =pstmt.executeQuery();
					while(rs.next()) {
						species_cnt[j]= rs.getInt(1);
					}
				}
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					rs.close();
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			return species_cnt;
		}
		
		//--------------배틀 시뮬레이션 용--------------------------//
		public double[] getBattledHeroAttack(String[] heroes, String army) {
			Hero_table ht = new Hero_table();
			String rival[] = getRival(army);
			boolean check =false;
			double total_attack=0, total_defense=0;
			double total_status[] = new double[5];	//0이 total_attack 1이 total_defense
			for(int i=0;i<heroes.length;i++) {
				for(int j=0;j<rival.length;j++) {//지휘하는 장군의 rival인지 검사
					if(heroes[i].equals(rival[j])) {
						check=true;
					}
				}
				
				ht=applied_comp(heroes[i]);
				total_attack =(ht.getTotal_attack()+3*ht.getTotal_str()+4*ht.getTotal_int()+2*ht.getTotal_mp());
				total_defense =(ht.getTotal_hp()+3*ht.getTotal_defense());
				if(check==true) {//지휘하는 장군의 rival일 경우 2배 공격력과 방어력
					total_attack = 2*total_attack;
					total_defense = 2*total_defense;
					check=false;
				}
				total_status[0]+=total_attack;
				total_status[1]+=total_defense;
			}
			return total_status;
			
		}
		
		public String[] getRival(String army) {
			getConnection();
			String rival[] = new String [100];
			int i =0;
			String sql="select rival from general where general_name in ("
					+ "select general_name from command where army_name=?)";
			try {
				pstmt = conn.prepareStatement(sql);
				pstmt.setString(1, army);
				rs = pstmt.executeQuery();
				while(rs.next()) {
					rival[i] = rs.getString("rival");
					i++;
				}
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}finally {
				try {
					rs.close();
					pstmt.close();
					conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			return rival;
			
			
		}
		
		
}
