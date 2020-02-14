package poll.plBean;

import lombok.Data;

@Data
public class PollListBean {

	private int num;
	private String question;
	private String sdate;
	private String edate;
	private String wdate;
	private int type;
	private int active;
}
