import java.util.Scanner;

class MakeFlatform {
	private char[][] game = new char[10][30];
	private int xs, ys; // start���� ��ǥ
	// ������ ��ǥ
	private int x1, y1;
	private int x2, y2;
	private int x3, y3;
	private int x4, y4;
	
	// �������� ��ǥ
	private int xt, yt;
	
	public MakeFlatform() {
		// TODO Auto-generated constructor stub
	}

	public void setBoard() {	//���� �� ���� �޼ҵ�
		//ó�� 0���� ��� �ʱ�ȭ�� 
		for (int i = 0; i < game.length; i++) {
			for (int j = 0; j < game[i].length; j++) {
				game[i][j] = '0';
			}
		}
		
		setPosition();	//ó�� ��ġ�� ������ ��ġ, ���� ��ġ ���� �޼ҵ�

	}

	public int getXs() {	//������ x��ǥ ����
		return xs;
	}

	public int getYs() {	//������ y��ǥ ����
		return ys;
	}

	public char[][] getGame() {	//������ ����
		return game;
	}

	public void setPosition() {	//ó�� ��ġ�� ������ ��ġ, ���� ��ġ ���� �޼ҵ�
		
		
		while (true) {
			// x�� 1~9�� �������� �������� ����1�� ���� ��ġ ����
			ys = (int) (Math.random() * 10); // ���� ������ǥ 0~9
			xs = (int) ((Math.random() * 9) + 1); // ���� ������ǥ 1~9

			y1 = (int) (Math.random() * 10);
			x1 = (int) ((Math.random() * 9) + 1);

			if ((ys == y1 && xs == x1) || Math.abs(xs - x1) == 1 || Math.abs(ys - y1) == 1) {
				// �� ��ǥ�� �����ϰų� x��ǥ�� y��ǥ�� 1�ۿ� ���̰� �ȳ��ٸ�(���� ������ ���輺 ����)
				// �ٽ� ����

			} else {	//�ƴ϶�� ��ġ ����
				game[ys][xs] = 'p';
				game[y1][x1] = '1';
				break;
			}
		}

		while(true){
		// x�� 11~14�� �������� ����2�� ���� ��ġ ����
			y2 = (int) (Math.random() * 10); // ���� ������ǥ 0~9
			x2 = (int) ((Math.random() * 4) + 11); // ���� ������ǥ 11~14
		
			if(ys==y1 && y1-y2 == 1)	//�������� ����1�� ���� y����ȿ� �ִµ� ����2�� ����1�� ��ĭ ���� ��ĭ �Ʒ��� �ִٸ�
			{							//���� �����Ǵ°��� ���� ���� ���ǹ�
				continue;	//�ٽ� �̴´�
			}
			else{
				game[y2][x2] = '2';
				break;
			}
		}
		
		
		
		// x�� 16~19�� �������� ����3�� ���� ��ġ ����
		y3 = (int) (Math.random() * 10); // ���� ������ǥ 0~9
		x3 = (int) ((Math.random() * 4) + 16); // ���� ������ǥ 16~19
		game[y3][x3] = '3';

		// x�� 21~24�� �������� ����4�� ���� ��ġ ����
		y4 = (int) (Math.random() * 10); // ���� ������ǥ 0~9
		x4 = (int) ((Math.random() * 4) + 21); // ���� ������ǥ 21~24
		game[y4][x4] = '4';

		// x�� 26~29�� �������� t�� ���� ��ġ ����
		yt = (int) (Math.random() * 10);// ���� ������ǥ 0~9
		xt = (int) ((Math.random() * 4) + 26);// ���� ������ǥ 26~29
		game[yt][xt] = 'T';

		//�游��� �޼ҵ�
		setRoad(xs, ys, x1, y1);	
		setRoad(x1, y1, x2, y2);
		setRoad(x2, y2, x3, y3);
		setRoad(x3, y3, x4, y4);
		setRoad(x4, y4, xt, yt);

	}

	public void setRoad(int x1, int y1, int x2, int y2) {	//���� ������ִ� �޼ҵ�
		// ���� �ִ��� ������ �Ÿ��� �����.
		// x1, y1�� ������ x2, y2�� �������� �Ѵ�
		
		int choose = 0;	//��� �������� ���� ���� ���� ���ϴ� ����
		
		int i = 0;
		int j = 0;

		if ((y1 - y2) > 0) { // y1, x1�� ���� ������ x2, y2�� ���� �������� �Ʒ��� �ִ� ���
			if ((x1 - x2) >= 0) { // y1, x1�� ���� ������ x2, y2�� ���� �������� �����ʿ� �ִ� ���
				// *y1,x1�� y2,x2���� �Ʒ��� �����ʿ� �ִ� ���� s���� ����1�� �� �����̴�

				if ((x1 - x2) == 0) { // x��ǥ������ ��ġ�� ���� ���
					choose = 0; // ���κ��� ���� ó���� ���̱� ������ ù ��츸 �����ϸ� ������ ���� ���� ������
				} else { // x1 > x2 �̸� ������ �������� �����ϴ� ���� ������ ��(���� ���⼺ ����)
					choose = 1;
				}
						
				if (choose == 1) {// x1, y1�������� �������� �����ϴ� ���� ����
					for (i = 0; i < (x1 - x2); i++) {
						game[y1][x1 - (i + 1)] = ' ';

					}
					for (j = 1; j < (y1 - y2); j++) {
						game[y1 - j][x1 - i] = ' ';

					}
				} else {// �������� �����ϴ� ���� ����
					for (i = 0; i < (y1 - y2); i++) {
						if (game[y1 - (i + 1)][x1] == '1')
							break;
						game[y1 - (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x1 - x2); j++) {
						game[y1 - i][x1 - j] = ' ';

					}
				}
			} else if (x1 - x2 < 0) { // ���ʿ� �ִ� ���
				choose = (int) (Math.random() * 2);

				if (game[y1][x1 + 1] == ' ') { // �����ʱ��� �Դ� ���̾��ٸ�
					choose = 0; // ������ �������� ��������
				} else if (game[y1 - 1][x1] == ' ') {// ���ʱ��� �Դ� ���̾��ٸ�
					choose = 1; // ������ ���������� ��������
				}
				if (choose == 1) {// �������� ���������� �����ϴ� ���� ����
					for (i = 0; i < (x2 - x1); i++) {
						game[y1][x1 + (i + 1)] = ' ';

					}
					for (j = 1; j < (y1 - y2); j++) {
						game[y1 - j][x1 + i] = ' ';

					}
				} else {// �������� �����ϴ� ���� ����

					for (i = 0; i < (y1 - y2); i++) {
						game[y1 - (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x2 - x1); j++) {
						game[y1 - i][x1 + j] = ' ';

					}
				}

			}
		} else if ((y1 - y2) < 0) { // x1, y1�� ���� ������ x2, y2���� ���� �ִ� ���
			if ((x1 - x2) >= 0) { // y1, x1�� ���� ������ x2, y2�� ���� �������� �����ʿ� �ִ� ���
				if ((x1 - x2) == 0) { // y1, x1�� x2, y2���� ���� �����鼭 �����ʿ� �ִ� ����
										// s���� ����1�� ���� ���̴�
					choose = 0;
				} else {// x1>x2�� ��� ������ �������� �����ϴ� ���� �������� (���� ���⼺ ����)
					choose = 1;
				}
						
				if (choose == 1) {// x1, y1�������� �������� �����ϴ� ���� ����
					for (i = 0; i < (x1 - x2); i++) {
						game[y1][x1 - (i + 1)] = ' ';

					}
					for (j = 1; j < (y2 - y1); j++) {
						game[y1 + j][x1 - i] = ' ';

					}
				} else {// �Ʒ������� �����ϴ� ���� ����
					for (i = 0; i < (y2 - y1); i++) {
						if (game[y1 + (i + 1)][x1] == '1')
							break;
						game[y1 + (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x1 - x2); j++) {
						game[y1 + i][x1 - j] = ' ';

					}
				}
			} else if (x1 - x2 < 0) { // ���ʿ� �ִ� ���
				choose = (int) (Math.random() * 2);

				if (game[y1][x1 + 1] == ' ') { // �����ʱ��� �Դ� ���̾��ٸ�
					choose = 0; // ������ �Ʒ������� ��������
				} else if (game[y1 + 1][x1] == ' ') {// �Ʒ� �ʱ��� �Դ� ���̾��ٸ�
					choose = 1; // ������ ���������� ��������
				}

				if (choose == 1) {// �������� ���������� �����ϴ� ���� ����
					for (i = 0; i < (x2 - x1); i++) {
						game[y1][x1 + (i + 1)] = ' ';

					}
					for (j = 1; j < (y2 - y1); j++) {
						game[y1 + j][x1 + i] = ' ';

					}
				} else {// �Ʒ������� �����ϴ� ���� ����
					for (i = 0; i < (y2 - y1); i++) {
						game[y1 + (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x2 - x1); j++) {
						game[y1 + i][x1 + j] = ' ';

					}
				}

			}
		} else {// y1�� y2�� ���� ���
			if ((x1 - x2) > 0) { // y1, x1�� ���� ������ x2, y2�� ���� �������� �����ʿ� �ִ� ���
									// �� ���� s���� ����1�� �� ����

				// x1, y1�������� �������� �����ϴ� ���� ����
				for (i = 1; i < (x1 - x2); i++) {
					game[y1][x1 - i] = ' ';

				}

			} else if ((x1 - x2) < 0) { // ���ʿ� �ִ� ���

				if (game[y1][x1 + 1] != ' ') { // ������� ���� ���� �Ծ��� ��� ��ġ���ʴ´ٸ�
					for (i = 1; i < (x2 - x1); i++) {
						game[y1][x1 + i] = ' ';

					}
				} else { // ��ģ�ٸ�

					choose = (int) (Math.random() * 2);// �Ʒ� �� �� �� �ϳ� ����

					if (choose == 1) { // �Ʒ������� ��ȸ
						game[y1 + 1][x1] = ' ';

						game[y1 + 2][x1] = ' ';

						for (j = 0; j < (x2 - x1); j++) {
							game[y1 + 2][x1 + (j + 1)] = ' ';

						}
						game[y1 + 1][x1 + j] = ' ';

					} else if (choose == 0) {// �������� ��ȸ
						game[y1 - 1][x1] = ' ';

						game[y1 - 2][x1] = ' ';

						for (j = 0; j < (x2 - x1); j++) {
							game[y1 - 2][x1 + (j + 1)] = ' ';

						}
						game[y1 - 1][x1 + j] = ' ';

					}

				}

			}
		}

	}

	public void addMaze(int y1, int x1, int y2, int x2) {// y1, x1�� ����� y2, x2�� �������̶� �Ѵ�

		
	}

}

class StartGame {
	private int ys, xs; // ���� ��ġ
	private char[][] game = new char[10][30];	//������
	private char diEast, diWest, diSouth, diNorth; // �� �� �ִ� ���� ��ǥ��
	private String east, west, south, north; // ���� ����
	private String[] ewsn=new String[4];	//�������� �� �� �ִ� �����̶�� �������� ������ ������ �迭
	Scanner sc;

	public StartGame(int ys, int xs, char[][] game) {
		sc = new Scanner(System.in);
		this.ys = ys;	//ys���� ����
		this.xs = xs;	//xs���� ����
		this.game = game;	//�������� ����
	}

	public String selectLevel() {	//���� ���� �޼ҵ�
		String level;
		while (true) {
			System.out.println("�ȳ�> ���� ���̵��� �������ּ���. ( �ʱ�/�߱�/��� ) ");
			System.out.print("�÷��̾�> ");
			level = sc.nextLine();
			if (level.equals("�ʱ�") || level.equals("�߱�") || level.equals("���"))
				//������ �ùٸ��� ���� �Ǿ����� ����
				return level;
			else {	//�ƴ϶�� �ٽ� ����
				System.out.println("�ȳ�> �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���");
				continue;
			}
		}
	}

	public int playGame() {// 0���Ͻ� ����, 1���Ͻ� retry
		int yp = ys, xp = xs; // ���� ��ġ ( ó���� ���� ��ġ�� �ʱ�ȭ )
		char boss; // ������ ������ �����ѹ� ����
		String direction; // �÷��̾ ������ ������ �ִ� ����
		boolean check = true; // �÷��̾ �� �� �ִ��� ������ üũ ����
		boolean bossCheck = true; // boss���� �̰���� ������ true�� �¸�, false�� �й�
		int numDirect;
		String level;	//�������� ���� ���ڿ� ����
		
		level = selectLevel();
		
		showMenual();
		
		while (true) {
			showBoard();	//�������� ���
			
			numDirect = checkDirec(yp, xp);	//���� ��ġ�κ��� ��� �������� �̵��� �� �ִ��� üũ�ϴ� �޼ҵ�
			
			switch(numDirect){//�� �� �ִ� ������ ���� ��ŭ case�� ������ ���
				case 1: 
					System.out.println("�ȳ�> �̵��� ������ �������ּ���. " + "("  +ewsn[0]+ ")");
					break;
				case 2:
					System.out.println("�ȳ�> �̵��� ������ �������ּ���. " + "("  +ewsn[0]+","+ewsn[1]+ ")");
					break;
				case 3:
					System.out.println("�ȳ�> �̵��� ������ �������ּ���. " + "("  +ewsn[0]+","+ewsn[1]+","+ewsn[2]+ ")");
					break;
				case 4:
					System.out.println("�ȳ�> �̵��� ������ �������ּ���. " + "("  +ewsn[0]+","+ewsn[1]+","+ewsn[2]+ ","+ewsn[3]+")");
					break;
				default :
					break;
				
			}
			
			System.out.println(" " + diNorth);
			System.out.println(diWest + "p" + diEast);
			System.out.println(" " + diSouth);
			System.out.print("�÷��̾�> ");
			direction = sc.nextLine();

			check = checkCanGo(direction);	//�� �� �ִ� �������� �Է��ߴ��� Ȯ���ϴ� �޼ҵ�
			
			if (check == true) {	//�� �� �ִٸ�
				if (direction.equals("��")) {	//������ ���ٸ�
					if (game[yp][xp + 1] == '1' || game[yp][xp + 1] == '2' || game[yp][xp + 1] == '3'
							|| game[yp][xp + 1] == '4') {//���� �濡 ������ �ִٸ�

						boss = game[yp][xp + 1];	//boss������ �� ��° ���������� ����

						if (yp == ys && xp == xs) {	//�������̶�� s�� �ڱ� ��ġ�� ����
							game[yp][xp] = 's';
						} else	//�ƴ϶��	������ �ڱ� ��ġ�� ����
							game[yp][xp] = ' ';

						game[yp][xp + 1] = 'p';	//�̵��� �ڸ��� p�� ����

						showBoard();	//������ ���

						bossCheck = fightBoss(boss, level);	//������ �߱������� �����ϴ� �޼ҵ�

						sc.nextLine();	//fightBoss�Լ����� ���� \n�� �޾��ִ� �뵵
						
						if (bossCheck == false) {	//�������� ���ٸ�
							return chooseRetry();
						}
						//�ƴ϶�� �Ѿ

					}
					
					if (game[yp][xp + 1] == 'T') {	//���� �̵��� �ڸ��� �������ڶ��
						
						game[yp][xp + 1] = 'p';	//�� �ڸ��� p�� ����
						
						if (yp == ys && xp == xs) {	//�������̶�� s�� �ڱ� ��ġ�� ����
							game[yp][xp] = 's';
						} else	//�ƴ϶��	������ �ڱ� ��ġ�� ����
							game[yp][xp] = ' ';

						showBoard();
						
						System.out.println("�ȳ�> ������ �߰��߽��ϴ�!!! Game Clear.");
						return chooseRetry();	//retry�� ������ �˾Ƴ��� �Լ�
					}

					game[yp][xp + 1] = 'p';	//�̵��� �ڸ��� p����

					if (yp == ys && xp == xs) {	//�������̶�� ���� ��ġ�� s����
						game[yp][xp] = 's';
					} else	//�ƴ϶�� ���� ��ġ�� ���� ����
						game[yp][xp] = ' ';

					xp++;	//�������� �̵�

					//*��, ��, ���� ���� ���⸸ �ٸ��� �˰����� ���� ���� ���� �ּ��� ���� ���� ����
					
				} else if (direction.equals("��")) {
					if (game[yp][xp - 1] == '1' || game[yp][xp - 1] == '2' || game[yp][xp - 1] == '3'
							|| game[yp][xp - 1] == '4') {

						boss = game[yp][xp - 1];

						if (yp == ys && xp == xs) {
							game[yp][xp] = 's';
						} else
							game[yp][xp] = ' ';

						game[yp][xp - 1] = 'p';
						showBoard();
						bossCheck = fightBoss(boss, level);
						sc.nextLine();
						if (bossCheck == false) {
							return chooseRetry();
						}

					}

					if (game[yp][xp - 1] == 'T') {
						game[yp][xp - 1] = 'p';
						if (yp == ys && xp == xs) {
							game[yp][xp] = 's';
						} else
							game[yp][xp] = ' ';

						showBoard();
						System.out.println("�ȳ�> ������ �߰��߽��ϴ�!!! Game Clear.");
						return chooseRetry();
					}

					game[yp][xp - 1] = 'p';

					if (yp == ys && xp == xs) {
						game[yp][xp] = 's';
					} else
						game[yp][xp] = ' ';
					xp--;	//�������� �̵�

				} else if (direction.equals("��")) {
					if (game[yp + 1][xp] == '1' || game[yp + 1][xp] == '2' || game[yp + 1][xp] == '3'
							|| game[yp + 1][xp] == '4') {

						boss = game[yp + 1][xp];

						if (yp == ys && xp == xs) {
							game[yp][xp] = 's';
						} else
							game[yp][xp] = ' ';

						game[yp + 1][xp] = 'p';
						showBoard();
						bossCheck = fightBoss(boss, level);
						sc.nextLine();
						if (bossCheck == false) {
							return chooseRetry();
						}

					}

					if (game[yp + 1][xp] == 'T') {
						game[yp + 1][xp] = 'p';
						if (yp == ys && xp == xs) {
							game[yp][xp] = 's';
						} else
							game[yp][xp] = ' ';

						showBoard();
						System.out.println("�ȳ�> ������ �߰��߽��ϴ�!!! Game Clear.");
						return chooseRetry();
					}

					game[yp + 1][xp] = 'p';

					if (yp == ys && xp == xs) {
						game[yp][xp] = 's';
					} else
						game[yp][xp] = ' ';
					yp++;	//�������� �̵�

				} else if (direction.equals("��")) {
					if (game[yp - 1][xp] == '1' || game[yp - 1][xp] == '2' || game[yp - 1][xp] == '3'
							|| game[yp - 1][xp] == '4') {
						boss = game[yp - 1][xp];

						if (yp == ys && xp == xs) {
							game[yp][xp] = 's';
						} else
							game[yp][xp] = ' ';

						game[yp - 1][xp] = 'p';
						showBoard();
						bossCheck = fightBoss(boss, level);
						sc.nextLine();

						if (bossCheck == false) {
							return chooseRetry();
						}

					}

					if (game[yp - 1][xp] == 'T') {
						game[yp - 1][xp] = 'p';

						if (yp == ys && xp == xs) {
							game[yp][xp] = 's';
						} else
							game[yp][xp] = ' ';

						showBoard();
						System.out.println("�ȳ�> ������ �߰��߽��ϴ�!!! Game Clear.");
						return chooseRetry();
					}

					game[yp - 1][xp] = 'p';

					if (yp == ys && xp == xs) {
						game[yp][xp] = 's';
					} else
						game[yp][xp] = ' ';
					yp--;	//�������� �̵�

				}
			} else {
				System.out.println("�ȳ�> �̵��� �� ���� �����̰ų� �߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���");
				continue;
			}
		}

	}

	public int chooseRetry() { // retry���� ������ ���ϴ� �޼ҵ�
		
		String retry;

		while (true) {
			System.out.println("�ȳ�> �ٽ� �����Ͻðڽ��ϱ�? [yes/no]");
			System.out.print("�÷��̾�> ");
			retry = sc.nextLine();
			if (retry.equals("yes")) {	//����� yes��� return 1
				return 1;
			} else if (retry.equals("no")) { // no��� return 0
				return 0;
			} else {	//�� ���� ����� ������ ����ϰ� �ٽ� ����
				System.out.println("�ȳ�> �߸��� �Է��Դϴ�. [yes/no] �� �߿� �����Ͽ��ֽʽÿ�.");
				continue;
			}
		}

	}

	public boolean fightBoss(char boss, String level) {	//������ �߱����� �÷��� ���� �޼ҵ�
		
		int count = 0;	//���� ���� Ƚ��
		int end;	//�� ���� ��Ʈ����ũ�� �ؾ��ϴ����� ���� ����
		boolean overlap = false; // �ߺ��˻� ���� true�� �ߺ�, false�� �ߺ��� �ƴϴ�
		int strike, ball, out;	//��ġ�� ���ڰ� ������ strike, ���ڸ� �°� ��ġ�� �ٸ��� ball, �� �ٸ��� out
		int chance = 0;	//�÷��̾ �� ��° ���� �ߴ��� �˷��ִ� ����
		boolean checkOut = true; // true�� out, false�� out�� �ƴ�
		
		int[] num;	//�÷��̾ �Է��� ���� ���� �迭
		int[] bossNum;	//������ �ڵ� ���õ� ���� ���� �迭
		
		// ������ ��ȣ�� ���� ���� ���̵��� �������� �����Ѵ�
		// ���̵��� ���� ���� �־����� ��ȸ�� ��������
		//1��° ������ 10, 2��°�� 8, 3��°�� 6, 4��°�� 4�̴�.
		if (boss == '1') {
			count = 10;
		} else if (boss == '2') {
			count = 8;
		} else if (boss == '3') {
			count = 6;
		} else if (boss == '4') {
			count = 4;
		}

		
		if (level.equals("�ʱ�")) {//�ʱ� ���̵��� ����� �� ���� ���� Ƚ���� 5ȸ �þ��.
			count += 5;
		} else if (level.equals("�߱�")) {//�߱� ���̵��� ����� �� ���� ���� Ƚ���� 1ȸ �þ��.
			count += 1;
		}
		if (level.equals("���")) {	//��� ���̵��� ����� �� 4�ڸ� �� �߱� ������ �ȴ�.
			num = new int[4];
			bossNum = new int[4];
			end = 4;
		} else {	//�� �ܿ��� 3�ڸ� �� �߱� ����
			num = new int[3]; // �÷��̾ �� ���ڵ�
			bossNum = new int[3]; // ������ �� ���ڵ�
			end = 3;
		}

		for (int i = 0; i < bossNum.length; i++) {	//������ ���� ���õǴ� ���� �ߺ� ���� �˻�
			overlap = false;	
			bossNum[i] = (int) (Math.random() * 10); // 0~9��������
			for (int j = 0; j < i; j++) {
				if (bossNum[j] == bossNum[i]) {	//���� ���ڰ� ������ �־��� ���ڵ�� ���ٸ�
					overlap = true;	//�ߺ��� true
					break;
				}
			}
			if (overlap == true) {//�ߺ��� true��� i�� �ϳ� ���̰� �ٽ� �ݺ�
				i--;
				continue;
			}
			//�ߺ��� �ƴ϶�� �Ѿ
		}
		
		System.out.println("�ȳ�> ���� " + boss + "�� �����Ͽ����ϴ�!!!");
		System.out.println("�ȳ�> ������ ���� �߱� ������ �����մϴ�.");
		System.out.println("�ȳ�> �� " + count + "���� ��ȸ�� �־����ϴ�.");
		System.out.println("�ȳ�> ������ ��ȸ ���� ������ ����ġ����!!");
		System.out.println();
		for (chance = 1; chance < count + 1; chance++) {	//count��ŭ�� ��ȸ�� �־�����

			//strike, ball, out�� �ʱ�ȭ
			strike = 0;
			ball = 0;
			out = 0;

			if (chance == count) {	//������ ��ȸ���
				System.out.println("�ȳ�> ������ ��ȸ�Դϴ�!!! ��������!" + "(" + chance + "/" + count + ")");
			} else {//�ƴ϶��
				System.out.println("�ȳ�> " + chance + "��° ��ȸ " + "(" + chance + "/" + count + ")");
			}

			//�÷��̾� �Է� ���ڵ� �ߺ� ���� Ȯ��
			for (int j = 0; j < bossNum.length; j++) {
				checkOut = true;
				overlap = false;
				System.out.println("�ȳ�> " + (j + 1) + "��° ���ڸ� �Է��ϼ���");
				System.out.print("�÷��̾�> ");			
				try {
					num[j] = sc.nextInt();
				} catch (Exception e) {	//int�� �ܿ� �Է��ϰų� �迭�� ũ�⸦ �ѱ�� exception
					sc.nextLine();
					System.out.println("�ȳ�> �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
					j--;
					continue;
				}
				if (num[j] > 9 || num[j] < 0) {	//���� 0�̻� 9���ϸ� �Է½�Ű���Ѵ�.
					System.out.println("�ȳ�> �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
					j--;
					continue;
				}
				for (int k = 0; k < j; k++) {
					if (num[k] == num[j]) {	//�Է��� ���� �� ������ �Էµ� ����� ���ٸ�
						overlap = true;
						break;
					}
				}
				if (overlap == true) {	//�ߺ��� true�̸� 
					System.out.println("�ȳ�> �̹� �Էµ� �����Դϴ�.");
					j--;
					continue;
				}
				//�ƴϸ� �Ѿ

				if (num[j] == bossNum[j]) {// �Է��� ���ڰ� ������ j��° ���ڿ� ���ٸ�
					strike++; // ��Ʈ����ũ!
					checkOut = false;
				}

				for (int k = 0; k < bossNum.length; k++) {
					if(k==j){	//k�� j�� ���ٸ� �׳� �Ѿ
						
					}
					else if (num[j] == bossNum[k]) { // i��° ���� �ܿ� �ٸ� ���ڿ� ���ٸ� ball
						ball++;
						checkOut = false;
					}

				}

				if (checkOut == true) { // �� �ƴ϶�� out!
					out++;
				}
			}
			System.out.println("boss> " + strike + " strike, " + ball + " ball, " + out + "out");

			if (strike == end) {	//��� ��Ȯ�� ����ٸ� true return
				System.out.println("�������Լ� �¸��ϼ̽��ϴ�!!! ���������� ���ư��ϴ�.");
				return true;
			}
		}
		//������ ��ȸ�ȿ� ���ߴ� ���� �����Ͽ����� false return
		System.out.println("�������Լ� �й��ϼ̽��ϴ�.....Game Over");
		return false;

	}

	public int checkDirec(int yp, int xp) {	//��� �������� �� �� �ִ����� Ȯ���ϴ� �޼ҵ�
		int i = 0;
		
		if (xp != 29 && game[yp][xp + 1] != '0') {	//x��ǥ�� �ǳ��� �ƴϸ鼭 ���� ���� ĭ�� ���� �ƴ϶��
			ewsn[i] = "��";	//���� �迭�� �ִ´�
			diEast = '-';
			i++;	//�迭�� ���� �ּҷ� �Ѿ
		} else {
			diEast = ' ';
		}
		if (xp != 0 && game[yp][xp - 1] != '0') {	//x��ǥ�� ��ó���� �ƴϸ鼭 ���� ���� ĭ�� ���� �ƴ϶��
			ewsn[i] = "��";//���� �迭�� �ִ´�
			diWest = '-';
			i++;	//�迭�� ���� �ּҷ� �Ѿ
		} else {
			diWest = ' ';
		}
		if (yp != 0 && game[yp - 1][xp] != '0') {	//y��ǥ�� �� ���� �ƴϸ鼭 ���� ���� ĭ�� ���� �ƴ϶��
			ewsn[i] = "��";//���� �迭�� �ִ´�
			diNorth = 'l';
			i++;	//�迭�� ���� �ּҷ� �Ѿ
		} else {
			diNorth = ' ';
		}
		if (yp != 9 && game[yp + 1][xp] != '0') {	//y��ǥ�� �� �Ʒ��� �ƴϸ鼭 ���� ���� ĭ�� ���� �ƴ϶��
			ewsn[i] = "��";	//���� �迭�� �ִ´�
			diSouth = 'l';
			i++;	//�迭�� ���� �ּҷ� �Ѿ
		} else {
			diSouth = ' ';
		}
		return i;

	}

	public boolean checkCanGo(String direction) {//�� �� �ִ� �������� üũ�ϴ� �޼ҵ�
		boolean check = true;
		for(int i=0;i<ewsn.length;i++ ){
			if (direction.equals(ewsn[i])) { // �� �� �ִ� �����̶��
				check = true;
				break;
			} else // �ƴ϶��
			check = false;
		}
		return check;
	}

	public void showMenual(){	//�޴����� �����ִ� �޼ҵ�
		System.out.println("*-------------------------*");
		System.out.println("�� 0 : ��                      ��");
		System.out.println("�� *, -, �� : ���� ���       ��");
		System.out.println("�� s : ���� ��ġ               ��");
		System.out.println("�� p : �÷��̾� ��ġ           ��");
		System.out.println("�� 1, 2, 3, 4 : ���� ��ġ    ��");
		System.out.println("�� T : ���� ��ġ               ��");
		System.out.println("*-------------------------*");
	}
	public void showBoard() {	//���� �������� �����ִ� �޼ҵ�
		int i;
		
		System.out.println("*-------------------------------*");

		//game�迭 ��ü ���
		for (i = 0; i < game.length; i++) {
			System.out.print("��");
			for (int j = 0; j < game[i].length; j++) {
				System.out.print(game[i][j]);
			}
			System.out.println("��");
		}

		System.out.println("*-------------------------------*");
	}

}

public class TestGame {
	public static void main(String[] args) {
		char[][] game = new char[10][30];	//���� �� �迭 10*30
		int xs, ys;	//ó�� ��ġ ����
		int retry;	//retry���� ����
		
		MakeFlatform mkf = new MakeFlatform();	//�� ����� Ŭ����

		while (true) {
			mkf.setBoard();	//���� �� ����
			
			//���� ��ǥ�� ������
			xs = mkf.getXs();	
			ys = mkf.getYs();	

			game = mkf.getGame();//�������� ������

			StartGame pg = new StartGame(ys, xs, game);	//������ �����ϴ� Ŭ����
			
			retry = pg.playGame();//���� �÷��� �޼ҵ�

			//retry 0�̸� ����, 1�̸� �ٽ� ����
			if (retry == 0) {
				System.out.println("������ ����˴ϴ�....");
				break;
			} else if (retry == 1) {
				System.out.println("������ �ٽ� �����մϴ�.....");
				continue;
			}
		}
	}
}
