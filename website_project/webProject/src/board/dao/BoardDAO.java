package board.dao;

import java.sql.*;
import java.util.ArrayList;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;

import com.sun.corba.se.impl.ior.GenericTaggedComponent;

import board.bean.BoardDTO;

public class BoardDAO {
	private Connection conn;
	private PreparedStatement pstmt;
	private ResultSet rs;
	private DataSource ds;
	
	
	public BoardDAO() {
		try {
			Context ctx = new InitialContext();
			ds = (DataSource)ctx.lookup("java:comp/env/jdbc/oracle");
		} catch (NamingException e) {
			e.printStackTrace();
		}
	}
	
	private static BoardDAO instance;
	
	public static BoardDAO getInstance(){
		if(instance==null){//null인 경우는 프로그램 첫 실행시 밖에 없다
			synchronized(BoardDAO.class){
				//현재 ()안에 클래스파일을 가지고 있으면 동기화
				//이 synchronized를 하는 사람은 처음 들어온 단 한명
				instance=new BoardDAO();
			}
		}
		return instance;
	}
	
	public void boardWrite(BoardDTO dto){
		
		String sql ="insert into board values("
				+ "seq_board.nextval,?,?,?,?,?,?,0,sysdate)";
		try {
			conn = ds.getConnection();
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1,dto.getId());
			pstmt.setString(2,dto.getName());
			pstmt.setString(3,dto.getOriginalFile());
			pstmt.setString(4,dto.getFilename());
			pstmt.setString(5,dto.getTitle());
			pstmt.setString(6,dto.getContent());
			pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
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
		
		
	}
	
	public ArrayList<BoardDTO> showList(int startNum, int endNum){
		ArrayList<BoardDTO> list = new ArrayList<BoardDTO>();
		try {
			conn=ds.getConnection();
			String sql="select * from"
					+ "(select rownum rn, aa.* from"
					+ "(select seq,id,name,original,filename,subject,content,hit"
					+ ",to_char(logtime,'YYYY.MM.DD') as logtime from board order by seq desc)aa)"
					+ "where rn>=? and rn<=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, startNum);
			pstmt.setInt(2, endNum);
			rs = pstmt.executeQuery();
			while(rs.next()){
				BoardDTO dto = new BoardDTO();
				dto.setSeq(rs.getInt("seq"));
				dto.setId(rs.getString("id"));
				dto.setName(rs.getString("name"));
				dto.setOriginalFile(rs.getString("original"));
				dto.setFilename(rs.getString("filename"));
				dto.setTitle(rs.getString("subject"));
				dto.setContent(rs.getString("content"));
				dto.setHit(rs.getInt("hit"));
				dto.setLogtime(rs.getString("logtime"));
				list.add(dto);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			list=null;
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
		
		
		
		
		return list;
	}
	
	public int countTotal(){
		int totalAt=0;
		try {
			String sql="select count(*) as cnt from board";
			conn=ds.getConnection();
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			rs.next();
			totalAt = rs.getInt("cnt");
		} catch (SQLException e) {
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
		
		return totalAt;
	}
	
	
	public BoardDTO boardView(int seq){
		BoardDTO dto = new BoardDTO();
		try {
			
			conn=ds.getConnection();
			String sql="select * from board where seq=?";
			pstmt=conn.prepareStatement(sql);
			pstmt.setInt(1,seq);
			rs=pstmt.executeQuery();
			rs.next();
			dto.setSeq(rs.getInt("seq"));
			dto.setId(rs.getString("id"));
			dto.setName(rs.getString("name"));
			dto.setOriginalFile(rs.getString("original"));
			dto.setFilename(rs.getString("filename"));
			dto.setContent(rs.getString("content"));
			dto.setTitle(rs.getString("subject"));
			dto.setHit(rs.getInt("hit"));
			dto.setLogtime(rs.getString("logtime"));
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			dto=null;
		}finally{
			try{
				if(rs!=null)rs.close();
				if(pstmt!=null)pstmt.close();
				if(conn!=null)conn.close();
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
		
		return dto;
		
		
	}
	
	public int hitUpdate(int seq){
		try {
			conn= ds.getConnection();
			String sql="update board set hit=hit+1 where seq=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setInt(1, seq);
			pstmt.executeUpdate();
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return  -1;
		}finally{
			try {
				if(pstmt!=null)pstmt.close();
				if(conn!=null)conn.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return  -1;
			}
			
			
		}
		return 1;
		
		
		
	}
	
	public void modifyForm(BoardDTO dto){
		try {
			conn = ds.getConnection();
			String sql = "update board set subject=?,content=? where seq=?";
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, dto.getTitle());
			pstmt.setString(2, dto.getContent());
			pstmt.setInt(3, dto.getSeq());
			pstmt.executeQuery();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
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
		
		
		
		
	}
	
	public void boardDelete(int seq){
		try {
			conn = ds.getConnection();
			String sql="delete board where seq=?";
			pstmt= conn.prepareStatement(sql);
			pstmt.setInt(1, seq);
			pstmt.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
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
		
		
		
	}
}
