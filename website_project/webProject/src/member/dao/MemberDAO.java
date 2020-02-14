package member.dao;

import java.sql.*;
import java.security.*;

import member.bean.MemberDTO;

//Database Bean
public class MemberDAO {

	private Connection conn;
	private PreparedStatement pstmt;
	private ResultSet rs;

	MemberDAO() {// 생성자
		try {// 드라이버 연결
			Class.forName("oracle.jdbc.driver.OracleDriver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}

	private static MemberDAO instance;

	public static MemberDAO getInstance(){
		if(instance==null){
			synchronized(MemberDAO.class){
				instance = new MemberDAO();
				
			}
		}
		return instance;
	}

	public void getConnection() {

		try {
			conn = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:orcl", "hr", "hr");

		} catch (SQLException e) {
			e.printStackTrace();

		}

	}
	
	public int write(MemberDTO dto){
		int su=0;
		getConnection();
		String sql = "insert into member values(?,?,?,?,?,?,?,?,?,?,?,?,sysdate)";
		try{
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, dto.getName());
			pstmt.setString(2, dto.getId());
			pstmt.setString(3, dto.getPwd());
			pstmt.setString(4, dto.getGender());
			pstmt.setString(5, dto.getEmail1());
			pstmt.setString(6, dto.getEmail2());
			pstmt.setString(7, dto.getTel1());
			pstmt.setString(8, dto.getTel2());
			pstmt.setString(9, dto.getTel3());
			pstmt.setString(10, dto.getZipcode());
			pstmt.setString(11, dto.getAddr1());
			pstmt.setString(12, dto.getAddr2());
			
			su=pstmt.executeUpdate();
			
			
		}catch(SQLException e){
			e.printStackTrace();
		}finally{
			try {
				if(pstmt!=null)pstmt.close();
				if(conn!=null)conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
		return su; 
	}
	
	public String login(String id, String pwd){
		String name=null;
		getConnection();
		String sql = "select * from member where id=? and pwd=? ";
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, id);
			pstmt.setString(2, pwd);
			rs = pstmt.executeQuery();
			if(rs.next()){
				name = rs.getString("name");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
				try {
					if(rs!=null)rs.close();
					if(pstmt!=null)pstmt.close();
					if(conn!=null)conn.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
		
		
		return name; 
	}
	
	public String encryptPwd(String pwd) throws Exception {
		MessageDigest md = MessageDigest.getInstance("SHA-256");
		byte[] mdResult = md.digest(pwd.getBytes("UTF-8"));
		sun.misc.BASE64Encoder encoder = new sun.misc.BASE64Encoder();
		String str = encoder.encode(mdResult);
		return str;
	}

}
