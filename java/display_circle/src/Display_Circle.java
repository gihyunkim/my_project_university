import java.awt.*;
import java.util.Scanner;
import javax.swing.*;

class TrafficLightPanel extends JPanel {

	public TrafficLightPanel() {// ���� �׸��� ���� �г� ����
		setPreferredSize(new Dimension(300, 200));// width : 300, height : 200
		setBackground(Color.black);// background : black
	}

	public void paintComponent(Graphics page) {//
		int su = 0; // ���� ��
		int[] x, y, circle;// ������ �񱳸� �ϱ� ���� �迭 ����
		boolean check = false;// ��ġ���� ���� Ȯ�κ���

		super.paintComponent(page);

		Scanner sc = new Scanner(System.in);// �Է� �Լ�
		System.out.print("�� ���� ���� �����ðڽ��ϱ�?? : ");

		su = sc.nextInt(); // ���ڸ� �Է¹޾� su�� �ִ´�.

		if (su <= 0 ) {	//0�� ���ϸ� �Է����� ��
			System.out.println("0�� �̻��� �Է����ּ���.....");
			System.exit(0);	//���α׷� ����
		}
		
		// �迭 ����
		x = new int[su];
		y = new int[su];
		circle = new int[su];

		// �ʱ� �� ũ��� ��ġ ���� ����
		circle[0] = (int) ((Math.random() * 200) + 5);// ũ�� ���� ����
		x[0] = (int) (Math.random() * (300 - circle[0]));// x�� ��ġ ���� ����
		y[0] = (int) (Math.random() * (200 - circle[0]));// y�� ��ġ ���� ����

		// �ʱ� �� ����
		page.setColor(Color.white);// ���� ���� : �Ͼ��
		page.fillOval(x[0], y[0], circle[0], circle[0]);

		for (int i = 1; i < su; i++) { // �� �ΰ� �̻� ���� ��

			check = false;// check ���� �ʱ�ȭ

			// (i+1)��° �� ũ��� ��ġ ���� ����
			circle[i] = (int) ((Math.random() * 200) + 5);
			x[i] = (int) (Math.random() * (300 - circle[i]));
			y[i] = (int) (Math.random() * (200 - circle[i]));

			for (int j = 0; j < i; j++) { // �� �� ����� ��ġ���� Ȯ��

				if (Math.sqrt((double) ((x[i] - x[j]) * (x[i] - x[j])) + ((y[i] - y[j]) * (y[i] - y[j]))) < (circle[i]
						+ circle[j])) {// ���鳢�� ��ġ�� �ʰ� �ϱ� ���� ����
					check = true;// ������ ���� ��ģ��
					break;
				}

			}

			if (check == true) // ��ģ�ٸ�
			{

				i--; // ���� ���������ʰ� �ٽ� ����

			} else { // ��ġ�� �ʴ´ٸ�

				// �� ����
				page.setColor(Color.white);
				page.fillOval(x[i], y[i], circle[i], circle[i]);

			}
		}
	}

}

public class Display_Circle {
	public static void main(String[] args) {// �����Լ�

		JFrame frame = new JFrame("Making Circle");// ������ ��ü ����
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// ��� ������ x��ư�� ������
																// ���α׷� ����
		frame.getContentPane().add(new TrafficLightPanel());// �г��� �����ӿ� ����
		frame.pack();// ������ ����ȭ ����
		frame.setVisible(true);// �������� ���̰� ����
	}
}
