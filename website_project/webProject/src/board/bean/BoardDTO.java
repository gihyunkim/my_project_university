package board.bean;

import lombok.Data;

@Data
public class BoardDTO {
	private String title;
	private String content;
	private String name;
	private String id;
	private int hit;
	private String logtime;
	private int seq;
	private String filename;
	private String originalFile;

}
