package poll.piBean;

import lombok.Data;

@Data
public class PollItemBean {
	private int listnum;
	private int itemnum;
	private String[] item;
	private int count;
}
