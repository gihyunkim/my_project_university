package poll.dao;

import java.sql.*;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;

import board.dao.BoardDAO;
import poll.piBean.PollItemBean;
import poll.plBean.PollListBean;

import java.util.Vector
;
public class PollMgr {
	
	private DataSource ds;
	
	public PollMgr() {
		try {
			Context ctx = new InitialContext();
			ds = (DataSource)ctx.lookup("java:comp/env/jdbc/oracle");
		} catch (NamingException e) {
			e.printStackTrace();
		}
	}
	
	private static PollMgr instance;
	
	public static PollMgr getInstance() {
		
		if(instance==null){//null인 경우는 프로그램 첫 실행시 밖에 없다
			synchronized(PollMgr.class){
				//현재 ()안에 클래스파일을 가지고 있으면 동기화
				//이 synchronized를 하는 사람은 처음 들어온 단 한명
				instance=new PollMgr();
			}
		}
		return instance;
	}
	
	
	public int getMaxNum() {
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = null;
		int maxNum = 0;
		try {
			con = ds.getConnection();
			sql = "select max(num) from polllist";
			pstmt = con.prepareStatement(sql);
			rs = pstmt.executeQuery();
			if(rs.next())
				maxNum = rs.getInt(1);
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			try {
				if(pstmt!=null)pstmt.close();
				if(con!=null)con.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return maxNum;
	}
	
	public boolean insertPoll(PollListBean plBean, PollItemBean piBean) {
		Connection con=null;
		PreparedStatement pstmt = null;
		boolean flag = false;
		String sql = null;
		
		try {
			con = ds.getConnection();
			sql = "insert into pollList(num,question,startdate,enddate,writedate,override,active)"+"values(seq_poll.nextval,?,?,?,sysdate,?,1)";
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1,  plBean.getQuestion());
			pstmt.setString(2,  plBean.getSdate());
			pstmt.setString(3,  plBean.getEdate());
			pstmt.setInt(4,  plBean.getType());
			int result = pstmt.executeUpdate();
			if(result==1) {
				sql = "insert into pollitem values(?,?,?,?)";
				pstmt = con.prepareStatement(sql);
				String item[] = piBean.getItem();
				int itemnum = getMaxNum();
				int j = 0;
				for(int i =0;i<item.length;i++) {
					if(item[i] == null || item[i].equals(""))
						continue;
					pstmt.setInt(1, itemnum);
					pstmt.setInt(2, i);
					pstmt.setString(3, item[i]);
					pstmt.setInt(4, 0);
					j = pstmt.executeUpdate();
				}
				if(j>0)
					flag = true;
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			try {
				if(pstmt!=null)pstmt.close();
				if(con!=null)con.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}		
		}
		return flag;
	}
	
	public Vector<PollListBean> getAllList(){
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = null;
		Vector<PollListBean> vlist = new Vector<PollListBean>();
		try {
			con = ds.getConnection();
			sql = "select * from pollList order by num desc";
			pstmt = con.prepareStatement(sql);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				PollListBean plBean = new PollListBean();
				plBean.setNum(rs.getInt("num"));
				plBean.setQuestion(rs.getString("question"));
				plBean.setSdate(rs.getString("startdate"));
				plBean.setEdate(rs.getString("enddate"));
				vlist.add(plBean);
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
				try {
					if(pstmt!=null)pstmt.close();
					if(con!=null)con.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
		return vlist;
	}
	
	public PollListBean getList(int num) {
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = null;
		PollListBean plBean = new PollListBean();
		try {
			con = ds.getConnection();
			if(num == 0)
				sql = "select * from pollList order by num desc";
			else
				sql="select * from pollList where num="+num;
			pstmt = con.prepareStatement(sql);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				plBean.setQuestion(rs.getString("question"));
				plBean.setType(rs.getInt("override"));
				plBean.setActive(rs.getInt("active"));
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			try {
				if(pstmt!=null)pstmt.close();
				if(con!=null)con.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return plBean;
	}
	
	public Vector<String> getItem(int num){
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = null;
		Vector<String> vlist = new Vector<String>();
		int maxNum = getMaxNum();
		try {
			con = ds.getConnection();
			if(num==0) {
				sql = "select item from pollItem where listnum=? order by listnum desc";
				pstmt = con.prepareStatement(sql);
				pstmt.setInt(1, maxNum);
			}else {
				sql = "select item from pollItem where listnum=?";
				pstmt = con.prepareStatement(sql);
				pstmt.setInt(1, num);
			}
			rs = pstmt.executeQuery();
			while(rs.next()) {
				vlist.add(rs.getString(1));
			}
		}catch(Exception e){
			e.printStackTrace();
		}finally {
			try {
				if(pstmt!=null)pstmt.close();
				if(con!=null)con.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return vlist;
	}
	public boolean updatePoll(int num, String[] itemnum) {
		Connection con = null;
		PreparedStatement pstmt = null;
		boolean flag = false;
		String sql = null;
		try {
			con = ds.getConnection();
			sql = "update pollItem set count=count+1 where listnum=? and itemnum=?";
			pstmt = con.prepareStatement(sql);
			if(num==0)
				num = getMaxNum();
			for(int i=0;i<itemnum.length;i++) {
				if(itemnum[i] == null || itemnum[i].equals(""))
					break;
				pstmt.setInt(1, num);
				pstmt.setInt(2, Integer.parseInt(itemnum[i]));
				int j = pstmt.executeUpdate();
				if(j>0)
					flag=true;
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			try {
				if(pstmt!=null)pstmt.close();
				if(con!=null)con.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return flag;
	}
	public Vector<PollItemBean> getView(int num){
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs= null;
		String sql = null;
		Vector<PollItemBean>vlist = new Vector<PollItemBean>();
		try {
			con = ds.getConnection();
			sql =" select item, count from pollitem where listnum=?";
			pstmt = con.prepareStatement(sql);
			if(num==0)
				pstmt.setInt(1, getMaxNum());
			else
				pstmt.setInt(1, num);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				PollItemBean piBean = new PollItemBean();
				String item[] = new String[1];
				item[0] = rs.getString(1);
				piBean.setItem(item);
				piBean.setCount(rs.getInt(2));
				vlist.add(piBean);
			}
			
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			try {
				if(pstmt!=null)pstmt.close();
				if(con!=null)con.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return vlist;
	}
	public int sumCount(int num) {
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs= null;
		String sql = null;
		int count = 0;
		try {
			con = ds.getConnection();
			sql = "select sum(count) from pollItem where listnum=?";
			pstmt = con.prepareStatement(sql);
			if(num==0)
				pstmt.setInt(1, getMaxNum());
			else
				pstmt.setInt(1, num);
			rs = pstmt.executeQuery();
			if(rs.next())
				count = rs.getInt(1);
			
			}catch(Exception e) {
				e.printStackTrace();
			}finally {
				try {
					if(pstmt!=null)pstmt.close();
					if(con!=null)con.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		
		return count;
	}
}
