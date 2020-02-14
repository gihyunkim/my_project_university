import java.awt.*;
import java.util.Scanner;
import javax.swing.*;

class TrafficLightPanel extends JPanel {

	public TrafficLightPanel() {// 원을 그리기 위한 패널 생성
		setPreferredSize(new Dimension(300, 200));// width : 300, height : 200
		setBackground(Color.black);// background : black
	}

	public void paintComponent(Graphics page) {//
		int su = 0; // 원의 수
		int[] x, y, circle;// 원끼리 비교를 하기 위한 배열 변수
		boolean check = false;// 겹치는지 여부 확인변수

		super.paintComponent(page);

		Scanner sc = new Scanner(System.in);// 입력 함수
		System.out.print("몇 개의 원을 넣으시겠습니까?? : ");

		su = sc.nextInt(); // 숫자를 입력받아 su에 넣는다.

		if (su <= 0 ) {	//0개 이하를 입력했을 시
			System.out.println("0개 이상을 입력해주세요.....");
			System.exit(0);	//프로그램 종료
		}
		
		// 배열 생성
		x = new int[su];
		y = new int[su];
		circle = new int[su];

		// 초기 원 크기와 위치 랜덤 설정
		circle[0] = (int) ((Math.random() * 200) + 5);// 크기 랜덤 설정
		x[0] = (int) (Math.random() * (300 - circle[0]));// x축 위치 랜덤 설정
		y[0] = (int) (Math.random() * (200 - circle[0]));// y축 위치 랜덤 설정

		// 초기 원 생성
		page.setColor(Color.white);// 원의 색깔 : 하얀색
		page.fillOval(x[0], y[0], circle[0], circle[0]);

		for (int i = 1; i < su; i++) { // 원 두개 이상 생성 시

			check = false;// check 변수 초기화

			// (i+1)번째 원 크기와 위치 랜덤 설정
			circle[i] = (int) ((Math.random() * 200) + 5);
			x[i] = (int) (Math.random() * (300 - circle[i]));
			y[i] = (int) (Math.random() * (200 - circle[i]));

			for (int j = 0; j < i; j++) { // 그 전 원들과 겹치는지 확인

				if (Math.sqrt((double) ((x[i] - x[j]) * (x[i] - x[j])) + ((y[i] - y[j]) * (y[i] - y[j]))) < (circle[i]
						+ circle[j])) {// 원들끼리 겹치지 않게 하기 위한 조건
					check = true;// 원들이 서로 겹친다
					break;
				}

			}

			if (check == true) // 겹친다면
			{

				i--; // 원을 생성하지않고 다시 설정

			} else { // 겹치지 않는다면

				// 원 생성
				page.setColor(Color.white);
				page.fillOval(x[i], y[i], circle[i], circle[i]);

			}
		}
	}

}

public class Display_Circle {
	public static void main(String[] args) {// 메인함수

		JFrame frame = new JFrame("Making Circle");// 프레임 객체 생성
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 상단 오른쪽 x버튼을 누르면
																// 프로그램 종료
		frame.getContentPane().add(new TrafficLightPanel());// 패널을 프레임에 적용
		frame.pack();// 프레임 최적화 설정
		frame.setVisible(true);// 프레임을 보이게 설정
	}
}
