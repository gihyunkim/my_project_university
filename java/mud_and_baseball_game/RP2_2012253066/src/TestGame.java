import java.util.Scanner;

class MakeFlatform {
	private char[][] game = new char[10][30];
	private int xs, ys; // start지점 좌표
	// 보스들 좌표
	private int x1, y1;
	private int x2, y2;
	private int x3, y3;
	private int x4, y4;
	
	// 보물상자 좌표
	private int xt, yt;
	
	public MakeFlatform() {
		// TODO Auto-generated constructor stub
	}

	public void setBoard() {	//게임 판 세팅 메소드
		//처음 0으로 모두 초기화함 
		for (int i = 0; i < game.length; i++) {
			for (int j = 0; j < game[i].length; j++) {
				game[i][j] = '0';
			}
		}
		
		setPosition();	//처음 위치와 보스들 위치, 보물 위치 설정 메소드

	}

	public int getXs() {	//시작점 x좌표 리턴
		return xs;
	}

	public int getYs() {	//시작점 y좌표 리턴
		return ys;
	}

	public char[][] getGame() {	//게임판 리턴
		return game;
	}

	public void setPosition() {	//처음 위치와 보스들 위치, 보물 위치 설정 메소드
		
		
		while (true) {
			// x가 1~9인 지역에서 시작점과 보스1을 랜덤 위치 설정
			ys = (int) (Math.random() * 10); // 행의 랜덤좌표 0~9
			xs = (int) ((Math.random() * 9) + 1); // 열의 랜덤좌표 1~9

			y1 = (int) (Math.random() * 10);
			x1 = (int) ((Math.random() * 9) + 1);

			if ((ys == y1 && xs == x1) || Math.abs(xs - x1) == 1 || Math.abs(ys - y1) == 1) {
				// 두 좌표가 동일하거나 x좌표나 y좌표가 1밖에 차이가 안난다면(길이 공유될 위험성 제거)
				// 다시 설정

			} else {	//아니라면 위치 세팅
				game[ys][xs] = 'p';
				game[y1][x1] = '1';
				break;
			}
		}

		while(true){
		// x가 11~14인 지역에서 보스2를 랜덤 위치 설정
			y2 = (int) (Math.random() * 10); // 행의 랜덤좌표 0~9
			x2 = (int) ((Math.random() * 4) + 11); // 열의 랜덤좌표 11~14
		
			if(ys==y1 && y1-y2 == 1)	//시작점과 보스1이 같은 y선상안에 있는데 보스2가 보스1과 한칸 위나 한칸 아래에 있다면
			{							//길이 공유되는것을 막기 위한 조건문
				continue;	//다시 뽑는다
			}
			else{
				game[y2][x2] = '2';
				break;
			}
		}
		
		
		
		// x가 16~19인 지역에서 보스3를 랜덤 위치 설정
		y3 = (int) (Math.random() * 10); // 행의 랜덤좌표 0~9
		x3 = (int) ((Math.random() * 4) + 16); // 열의 랜덤좌표 16~19
		game[y3][x3] = '3';

		// x가 21~24인 지역에서 보스4를 랜덤 위치 설정
		y4 = (int) (Math.random() * 10); // 행의 랜덤좌표 0~9
		x4 = (int) ((Math.random() * 4) + 21); // 열의 랜덤좌표 21~24
		game[y4][x4] = '4';

		// x가 26~29인 지역에서 t를 랜덤 위치 설정
		yt = (int) (Math.random() * 10);// 행의 랜덤좌표 0~9
		xt = (int) ((Math.random() * 4) + 26);// 열의 랜덤좌표 26~29
		game[yt][xt] = 'T';

		//길만드는 메소드
		setRoad(xs, ys, x1, y1);	
		setRoad(x1, y1, x2, y2);
		setRoad(x2, y2, x3, y3);
		setRoad(x3, y3, x4, y4);
		setRoad(x4, y4, xt, yt);

	}

	public void setRoad(int x1, int y1, int x2, int y2) {	//길을 만들어주는 메소드
		// 길은 최대한 최적의 거리로 만든다.
		// x1, y1이 시작점 x2, y2를 끝점으로 한다
		
		int choose = 0;	//어느 방향으로 길을 뚫을 건지 정하는 변수
		
		int i = 0;
		int j = 0;

		if ((y1 - y2) > 0) { // y1, x1을 갖는 지점이 x2, y2를 갖는 지점보다 아래에 있는 경우
			if ((x1 - x2) >= 0) { // y1, x1을 갖는 지점이 x2, y2를 갖는 지점보다 오른쪽에 있는 경우
				// *y1,x1이 y2,x2보다 아래에 오른쪽에 있는 경우는 s에서 보스1로 갈 때뿐이다

				if ((x1 - x2) == 0) { // x좌표에서의 위치가 같을 경우
					choose = 0; // 끝부분은 따로 처리할 것이기 때문에 첫 경우만 생각하면 무조건 위로 길을 만들면됨
				} else { // x1 > x2 이면 무조건 왼쪽으로 시작하는 길을 만들어야 함(길의 복잡성 제거)
					choose = 1;
				}
						
				if (choose == 1) {// x1, y1지점에서 왼쪽으로 시작하는 길을 만듬
					for (i = 0; i < (x1 - x2); i++) {
						game[y1][x1 - (i + 1)] = ' ';

					}
					for (j = 1; j < (y1 - y2); j++) {
						game[y1 - j][x1 - i] = ' ';

					}
				} else {// 위쪽으로 시작하는 길을 만듬
					for (i = 0; i < (y1 - y2); i++) {
						if (game[y1 - (i + 1)][x1] == '1')
							break;
						game[y1 - (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x1 - x2); j++) {
						game[y1 - i][x1 - j] = ' ';

					}
				}
			} else if (x1 - x2 < 0) { // 왼쪽에 있는 경우
				choose = (int) (Math.random() * 2);

				if (game[y1][x1 + 1] == ' ') { // 오른쪽길이 왔던 길이었다면
					choose = 0; // 무조건 위쪽으로 만들어야함
				} else if (game[y1 - 1][x1] == ' ') {// 위쪽길이 왔던 길이었다면
					choose = 1; // 무조건 오른쪽으로 만들어야함
				}
				if (choose == 1) {// 지점에서 오른쪽으로 시작하는 길을 만듬
					for (i = 0; i < (x2 - x1); i++) {
						game[y1][x1 + (i + 1)] = ' ';

					}
					for (j = 1; j < (y1 - y2); j++) {
						game[y1 - j][x1 + i] = ' ';

					}
				} else {// 위쪽으로 시작하는 길을 만듬

					for (i = 0; i < (y1 - y2); i++) {
						game[y1 - (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x2 - x1); j++) {
						game[y1 - i][x1 + j] = ' ';

					}
				}

			}
		} else if ((y1 - y2) < 0) { // x1, y1을 갖는 지점이 x2, y2보다 위에 있는 경우
			if ((x1 - x2) >= 0) { // y1, x1을 갖는 지점이 x2, y2를 갖는 지점보다 오른쪽에 있는 경우
				if ((x1 - x2) == 0) { // y1, x1이 x2, y2보다 위에 있으면서 오른쪽에 있는 경우는
										// s에서 보스1로 갈때 뿐이다
					choose = 0;
				} else {// x1>x2일 경우 무조건 왼쪽으로 시작하는 길을 만들어야함 (길의 복잡성 제거)
					choose = 1;
				}
						
				if (choose == 1) {// x1, y1지점에서 왼쪽으로 시작하는 길을 만듬
					for (i = 0; i < (x1 - x2); i++) {
						game[y1][x1 - (i + 1)] = ' ';

					}
					for (j = 1; j < (y2 - y1); j++) {
						game[y1 + j][x1 - i] = ' ';

					}
				} else {// 아래쪽으로 시작하는 길을 만듬
					for (i = 0; i < (y2 - y1); i++) {
						if (game[y1 + (i + 1)][x1] == '1')
							break;
						game[y1 + (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x1 - x2); j++) {
						game[y1 + i][x1 - j] = ' ';

					}
				}
			} else if (x1 - x2 < 0) { // 왼쪽에 있는 경우
				choose = (int) (Math.random() * 2);

				if (game[y1][x1 + 1] == ' ') { // 오른쪽길이 왔던 길이었다면
					choose = 0; // 무조건 아래쪽으로 만들어야함
				} else if (game[y1 + 1][x1] == ' ') {// 아래 쪽길이 왔던 길이었다면
					choose = 1; // 무조건 오른쪽으로 만들어야함
				}

				if (choose == 1) {// 지점에서 오른쪽으로 시작하는 길을 만듬
					for (i = 0; i < (x2 - x1); i++) {
						game[y1][x1 + (i + 1)] = ' ';

					}
					for (j = 1; j < (y2 - y1); j++) {
						game[y1 + j][x1 + i] = ' ';

					}
				} else {// 아래쪽으로 시작하는 길을 만듬
					for (i = 0; i < (y2 - y1); i++) {
						game[y1 + (i + 1)][x1] = ' ';

					}
					for (j = 1; j < (x2 - x1); j++) {
						game[y1 + i][x1 + j] = ' ';

					}
				}

			}
		} else {// y1과 y2가 같은 경우
			if ((x1 - x2) > 0) { // y1, x1을 갖는 지점이 x2, y2를 갖는 지점보다 오른쪽에 있는 경우
									// 이 경우는 s에서 보스1갈 때 뿐임

				// x1, y1지점에서 왼쪽으로 시작하는 길을 만듬
				for (i = 1; i < (x1 - x2); i++) {
					game[y1][x1 - i] = ' ';

				}

			} else if ((x1 - x2) < 0) { // 왼쪽에 있는 경우

				if (game[y1][x1 + 1] != ' ') { // 만드려는 길이 내가 왔었던 길과 겹치지않는다면
					for (i = 1; i < (x2 - x1); i++) {
						game[y1][x1 + i] = ' ';

					}
				} else { // 겹친다면

					choose = (int) (Math.random() * 2);// 아래 위 둘 중 하나 선택

					if (choose == 1) { // 아래쪽으로 우회
						game[y1 + 1][x1] = ' ';

						game[y1 + 2][x1] = ' ';

						for (j = 0; j < (x2 - x1); j++) {
							game[y1 + 2][x1 + (j + 1)] = ' ';

						}
						game[y1 + 1][x1 + j] = ' ';

					} else if (choose == 0) {// 위쪽으로 우회
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

	public void addMaze(int y1, int x1, int y2, int x2) {// y1, x1을 출발점 y2, x2를 도착점이라 한다

		
	}

}

class StartGame {
	private int ys, xs; // 시작 위치
	private char[][] game = new char[10][30];	//게임판
	private char diEast, diWest, diSouth, diNorth; // 갈 수 있는 방향 지표기
	private String east, west, south, north; // 방향 변수
	private String[] ewsn=new String[4];	//방위들을 갈 수 있는 방향이라면 동서남북 순서로 저장할 배열
	Scanner sc;

	public StartGame(int ys, int xs, char[][] game) {
		sc = new Scanner(System.in);
		this.ys = ys;	//ys값을 얻어옴
		this.xs = xs;	//xs값을 얻어옴
		this.game = game;	//게임판을 얻어옴
	}

	public String selectLevel() {	//레벨 설정 메소드
		String level;
		while (true) {
			System.out.println("안내> 게임 난이도를 선택해주세요. ( 초급/중급/고급 ) ");
			System.out.print("플레이어> ");
			level = sc.nextLine();
			if (level.equals("초급") || level.equals("중급") || level.equals("고급"))
				//레벨이 올바르게 설정 되었으면 리턴
				return level;
			else {	//아니라면 다시 설정
				System.out.println("안내> 잘못된 입력입니다. 다시 입력해주세요");
				continue;
			}
		}
	}

	public int playGame() {// 0리턴시 종료, 1리턴시 retry
		int yp = ys, xp = xs; // 현재 위치 ( 처음은 시작 위치로 초기화 )
		char boss; // 보스전 들어가기전 보스넘버 기억용
		String direction; // 플레이어가 가려는 방향을 넣는 변수
		boolean check = true; // 플레이어가 갈 수 있는지 없는지 체크 변수
		boolean bossCheck = true; // boss에게 이겼는지 졌는지 true면 승리, false면 패배
		int numDirect;
		String level;	//레벨값을 넣을 문자열 변수
		
		level = selectLevel();
		
		showMenual();
		
		while (true) {
			showBoard();	//보드판을 출력
			
			numDirect = checkDirec(yp, xp);	//현재 위치로부터 어느 방향으로 이동할 수 있는지 체크하는 메소드
			
			switch(numDirect){//갈 수 있는 방향의 갯수 만큼 case로 나눠서 출력
				case 1: 
					System.out.println("안내> 이동할 방향을 선택해주세요. " + "("  +ewsn[0]+ ")");
					break;
				case 2:
					System.out.println("안내> 이동할 방향을 선택해주세요. " + "("  +ewsn[0]+","+ewsn[1]+ ")");
					break;
				case 3:
					System.out.println("안내> 이동할 방향을 선택해주세요. " + "("  +ewsn[0]+","+ewsn[1]+","+ewsn[2]+ ")");
					break;
				case 4:
					System.out.println("안내> 이동할 방향을 선택해주세요. " + "("  +ewsn[0]+","+ewsn[1]+","+ewsn[2]+ ","+ewsn[3]+")");
					break;
				default :
					break;
				
			}
			
			System.out.println(" " + diNorth);
			System.out.println(diWest + "p" + diEast);
			System.out.println(" " + diSouth);
			System.out.print("플레이어> ");
			direction = sc.nextLine();

			check = checkCanGo(direction);	//갈 수 있는 방향으로 입력했는지 확인하는 메소드
			
			if (check == true) {	//갈 수 있다면
				if (direction.equals("동")) {	//동으로 간다면
					if (game[yp][xp + 1] == '1' || game[yp][xp + 1] == '2' || game[yp][xp + 1] == '3'
							|| game[yp][xp + 1] == '4') {//가는 길에 보스가 있다면

						boss = game[yp][xp + 1];	//boss변수에 몇 번째 보스인지를 저장

						if (yp == ys && xp == xs) {	//시작점이라면 s를 자기 위치에 삽입
							game[yp][xp] = 's';
						} else	//아니라면	공백을 자기 위치에 삽입
							game[yp][xp] = ' ';

						game[yp][xp + 1] = 'p';	//이동할 자리에 p를 삽입

						showBoard();	//게임판 출력

						bossCheck = fightBoss(boss, level);	//보스와 야구게임을 시행하는 메소드

						sc.nextLine();	//fightBoss함수에서 나온 \n을 받아주는 용도
						
						if (bossCheck == false) {	//보스한테 졌다면
							return chooseRetry();
						}
						//아니라면 넘어감

					}
					
					if (game[yp][xp + 1] == 'T') {	//다음 이동할 자리가 보물상자라면
						
						game[yp][xp + 1] = 'p';	//그 자리에 p를 삽입
						
						if (yp == ys && xp == xs) {	//시작점이라면 s를 자기 위치에 삽입
							game[yp][xp] = 's';
						} else	//아니라면	공백을 자기 위치에 삽입
							game[yp][xp] = ' ';

						showBoard();
						
						System.out.println("안내> 보물을 발견했습니다!!! Game Clear.");
						return chooseRetry();	//retry할 것인지 알아내는 함수
					}

					game[yp][xp + 1] = 'p';	//이동할 자리에 p삽입

					if (yp == ys && xp == xs) {	//시작점이라면 현재 위치에 s삽입
						game[yp][xp] = 's';
					} else	//아니라면 현재 위치에 공백 삽입
						game[yp][xp] = ' ';

					xp++;	//동쪽으로 이동

					//*서, 남, 북은 가는 방향만 다르고 알고리즘은 동과 같음 따라서 주석을 따로 적지 않음
					
				} else if (direction.equals("서")) {
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
						System.out.println("안내> 보물을 발견했습니다!!! Game Clear.");
						return chooseRetry();
					}

					game[yp][xp - 1] = 'p';

					if (yp == ys && xp == xs) {
						game[yp][xp] = 's';
					} else
						game[yp][xp] = ' ';
					xp--;	//서쪽으로 이동

				} else if (direction.equals("남")) {
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
						System.out.println("안내> 보물을 발견했습니다!!! Game Clear.");
						return chooseRetry();
					}

					game[yp + 1][xp] = 'p';

					if (yp == ys && xp == xs) {
						game[yp][xp] = 's';
					} else
						game[yp][xp] = ' ';
					yp++;	//남쪽으로 이동

				} else if (direction.equals("북")) {
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
						System.out.println("안내> 보물을 발견했습니다!!! Game Clear.");
						return chooseRetry();
					}

					game[yp - 1][xp] = 'p';

					if (yp == ys && xp == xs) {
						game[yp][xp] = 's';
					} else
						game[yp][xp] = ' ';
					yp--;	//북쪽으로 이동

				}
			} else {
				System.out.println("안내> 이동할 수 없는 방향이거나 잘못된 입력입니다. 다시 입력하세요");
				continue;
			}
		}

	}

	public int chooseRetry() { // retry할지 안할지 정하는 메소드
		
		String retry;

		while (true) {
			System.out.println("안내> 다시 시작하시겠습니까? [yes/no]");
			System.out.print("플레이어> ");
			retry = sc.nextLine();
			if (retry.equals("yes")) {	//대답이 yes라면 return 1
				return 1;
			} else if (retry.equals("no")) { // no라면 return 0
				return 0;
			} else {	//그 외의 대답은 오류문 출력하고 다시 물음
				System.out.println("안내> 잘못된 입력입니다. [yes/no] 둘 중에 선택하여주십시오.");
				continue;
			}
		}

	}

	public boolean fightBoss(char boss, String level) {	//보스와 야구게임 플레이 시행 메소드
		
		int count = 0;	//도전 가능 횟수
		int end;	//몇 개의 스트라이크를 해야하는지에 대한 변수
		boolean overlap = false; // 중복검사 변수 true면 중복, false면 중복이 아니다
		int strike, ball, out;	//위치와 숫자가 맞으면 strike, 숫자만 맞고 위치는 다르면 ball, 다 다르면 out
		int chance = 0;	//플레이어가 몇 번째 도전 했는지 알려주는 변수
		boolean checkOut = true; // true면 out, false면 out이 아님
		
		int[] num;	//플레이어가 입력한 숫자 보관 배열
		int[] bossNum;	//보스의 자동 선택된 숫자 보관 배열
		
		// 보스는 번호가 높을 수록 난이도가 높음으로 설정한다
		// 난이도가 높을 수록 주어지는 기회가 낮아진다
		//1번째 보스는 10, 2번째는 8, 3번째는 6, 4번째는 4이다.
		if (boss == '1') {
			count = 10;
		} else if (boss == '2') {
			count = 8;
		} else if (boss == '3') {
			count = 6;
		} else if (boss == '4') {
			count = 4;
		}

		
		if (level.equals("초급")) {//초급 난이도를 골랐을 시 도전 가능 횟수가 5회 늘어난다.
			count += 5;
		} else if (level.equals("중급")) {//중급 난이도를 골랐을 시 도전 가능 횟수가 1회 늘어난다.
			count += 1;
		}
		if (level.equals("고급")) {	//고급 난이도를 골랐을 시 4자리 수 야구 게임이 된다.
			num = new int[4];
			bossNum = new int[4];
			end = 4;
		} else {	//그 외에는 3자리 수 야구 게임
			num = new int[3]; // 플레이어가 고른 숫자들
			bossNum = new int[3]; // 보스가 고른 숫자들
			end = 3;
		}

		for (int i = 0; i < bossNum.length; i++) {	//보스의 랜덤 선택되는 숫자 중복 여부 검사
			overlap = false;	
			bossNum[i] = (int) (Math.random() * 10); // 0~9랜덤숫자
			for (int j = 0; j < i; j++) {
				if (bossNum[j] == bossNum[i]) {	//현재 숫자가 이전에 있었던 숫자들과 같다면
					overlap = true;	//중복은 true
					break;
				}
			}
			if (overlap == true) {//중복이 true라면 i를 하나 줄이고 다시 반복
				i--;
				continue;
			}
			//중복이 아니라면 넘어감
		}
		
		System.out.println("안내> 보스 " + boss + "이 출현하였습니다!!!");
		System.out.println("안내> 보스와 숫자 야구 게임을 진행합니다.");
		System.out.println("안내> 총 " + count + "번의 기회가 주어집니다.");
		System.out.println("안내> 정해진 기회 내에 보스를 물리치세요!!");
		System.out.println();
		for (chance = 1; chance < count + 1; chance++) {	//count만큼의 기회가 주어진다

			//strike, ball, out값 초기화
			strike = 0;
			ball = 0;
			out = 0;

			if (chance == count) {	//마지막 기회라면
				System.out.println("안내> 마지막 기회입니다!!! 힘내세요!" + "(" + chance + "/" + count + ")");
			} else {//아니라면
				System.out.println("안내> " + chance + "번째 기회 " + "(" + chance + "/" + count + ")");
			}

			//플레이어 입력 숫자들 중복 여부 확인
			for (int j = 0; j < bossNum.length; j++) {
				checkOut = true;
				overlap = false;
				System.out.println("안내> " + (j + 1) + "번째 숫자를 입력하세요");
				System.out.print("플레이어> ");			
				try {
					num[j] = sc.nextInt();
				} catch (Exception e) {	//int형 외에 입력하거나 배열의 크기를 넘기면 exception
					sc.nextLine();
					System.out.println("안내> 잘못된 입력입니다. 다시 입력해주세요.");
					j--;
					continue;
				}
				if (num[j] > 9 || num[j] < 0) {	//수는 0이상 9이하만 입력시키게한다.
					System.out.println("안내> 잘못된 입력입니다. 다시 입력해주세요.");
					j--;
					continue;
				}
				for (int k = 0; k < j; k++) {
					if (num[k] == num[j]) {	//입력한 수가 그 이전에 입력된 수들과 같다면
						overlap = true;
						break;
					}
				}
				if (overlap == true) {	//중복이 true이면 
					System.out.println("안내> 이미 입력된 숫자입니다.");
					j--;
					continue;
				}
				//아니면 넘어감

				if (num[j] == bossNum[j]) {// 입력한 숫자가 보스의 j번째 숫자와 같다면
					strike++; // 스트라이크!
					checkOut = false;
				}

				for (int k = 0; k < bossNum.length; k++) {
					if(k==j){	//k와 j가 같다면 그냥 넘어감
						
					}
					else if (num[j] == bossNum[k]) { // i번째 숫자 외에 다른 숫자와 같다면 ball
						ball++;
						checkOut = false;
					}

				}

				if (checkOut == true) { // 다 아니라면 out!
					out++;
				}
			}
			System.out.println("boss> " + strike + " strike, " + ball + " ball, " + out + "out");

			if (strike == end) {	//모두 정확히 맞췄다면 true return
				System.out.println("보스에게서 승리하셨습니다!!! 게임판으로 돌아갑니다.");
				return true;
			}
		}
		//정해진 기회안에 맞추는 것을 실패하였으면 false return
		System.out.println("보스에게서 패배하셨습니다.....Game Over");
		return false;

	}

	public int checkDirec(int yp, int xp) {	//어느 방향으로 갈 수 있는지를 확인하는 메소드
		int i = 0;
		
		if (xp != 29 && game[yp][xp + 1] != '0') {	//x좌표가 맨끝이 아니면서 다음 동쪽 칸이 벽이 아니라면
			ewsn[i] = "동";	//동을 배열에 넣는다
			diEast = '-';
			i++;	//배열의 다음 주소로 넘어감
		} else {
			diEast = ' ';
		}
		if (xp != 0 && game[yp][xp - 1] != '0') {	//x좌표가 맨처음이 아니면서 다음 서쪽 칸이 벽이 아니라면
			ewsn[i] = "서";//서를 배열에 넣는다
			diWest = '-';
			i++;	//배열의 다음 주소로 넘어감
		} else {
			diWest = ' ';
		}
		if (yp != 0 && game[yp - 1][xp] != '0') {	//y좌표가 맨 위가 아니면서 다음 북쪽 칸이 벽이 아니라면
			ewsn[i] = "북";//북을 배열에 넣는다
			diNorth = 'l';
			i++;	//배열의 다음 주소로 넘어감
		} else {
			diNorth = ' ';
		}
		if (yp != 9 && game[yp + 1][xp] != '0') {	//y좌표가 맨 아래가 아니면서 다음 남쪽 칸이 벽이 아니라면
			ewsn[i] = "남";	//남을 배열에 넣는다
			diSouth = 'l';
			i++;	//배열의 다음 주소로 넘어감
		} else {
			diSouth = ' ';
		}
		return i;

	}

	public boolean checkCanGo(String direction) {//갈 수 있는 방향인지 체크하는 메소드
		boolean check = true;
		for(int i=0;i<ewsn.length;i++ ){
			if (direction.equals(ewsn[i])) { // 갈 수 있는 방향이라면
				check = true;
				break;
			} else // 아니라면
			check = false;
		}
		return check;
	}

	public void showMenual(){	//메뉴얼을 보여주는 메소드
		System.out.println("*-------------------------*");
		System.out.println("ㅣ 0 : 벽                      ㅣ");
		System.out.println("ㅣ *, -, ㅣ : 게임 경계       ㅣ");
		System.out.println("ㅣ s : 시작 위치               ㅣ");
		System.out.println("ㅣ p : 플레이어 위치           ㅣ");
		System.out.println("ㅣ 1, 2, 3, 4 : 보스 위치    ㅣ");
		System.out.println("ㅣ T : 보물 위치               ㅣ");
		System.out.println("*-------------------------*");
	}
	public void showBoard() {	//현재 게임판을 보여주는 메소드
		int i;
		
		System.out.println("*-------------------------------*");

		//game배열 전체 출력
		for (i = 0; i < game.length; i++) {
			System.out.print("ㅣ");
			for (int j = 0; j < game[i].length; j++) {
				System.out.print(game[i][j]);
			}
			System.out.println("ㅣ");
		}

		System.out.println("*-------------------------------*");
	}

}

public class TestGame {
	public static void main(String[] args) {
		char[][] game = new char[10][30];	//게임 판 배열 10*30
		int xs, ys;	//처음 위치 변수
		int retry;	//retry여부 변수
		
		MakeFlatform mkf = new MakeFlatform();	//판 만드는 클래스

		while (true) {
			mkf.setBoard();	//게임 판 세팅
			
			//시작 좌표를 가져옴
			xs = mkf.getXs();	
			ys = mkf.getYs();	

			game = mkf.getGame();//게임판을 가져옴

			StartGame pg = new StartGame(ys, xs, game);	//게임을 구동하는 클래스
			
			retry = pg.playGame();//게임 플레이 메소드

			//retry 0이면 종료, 1이면 다시 시작
			if (retry == 0) {
				System.out.println("게임이 종료됩니다....");
				break;
			} else if (retry == 1) {
				System.out.println("게임을 다시 시작합니다.....");
				continue;
			}
		}
	}
}
