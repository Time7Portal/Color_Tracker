#include <iostream>
#include <opencv2\opencv.hpp>


int main()
{
	// �Ӱ谪
	int thres = 64;
	int index = 0;
	int bCount = 0;
	int wCount = 0;
	int bDrawX = 0;
	int bDrawY = 0;
	int wDrawX = 0;
	int wDrawY = 0;

	// �̹��� ����
	cv::Mat image;
	cv::Mat image_gray;
	cv::Mat image_output;

	// ī�޶� ����
	cv::VideoCapture camera;
	// camera.open(0); // ��ķ
	camera.open("E:\\������Ʈ\\OpenCV\\BobRoss.mp4"); // ���� ������
	if (!camera.isOpened())
	{
		return 0;
	}

	// ������ ����
	cv::namedWindow("ī�޶�", 1);
	cv::namedWindow("ó�����", 1);

	// Ʈ���� �ֱ�
	cv::createTrackbar("����", "ó�����", &thres, 64, NULL);

	// �ǽð� ���
	while (1)
	{
		// ī�޶� �̹��� ����
		camera >> image;

		// �¿����
		//cv::flip(image, image, 1);

		// �̹��� �ػ� ���
		cv::resize(image, image_output, cv::Size(640, 480));

		// ����ȭ
		//cv::cvtColor(image_output, image_gray, CV_RGB2GRAY);
		//cv::threshold(image_gray, image_output, (thres * 2), 255, CV_THRESH_BINARY);

		// Ž���� �ʱ�ȭ
		bCount = 0;
		bDrawX = 0;
		bDrawY = 0;
		wCount = 0;
		wDrawX = 0;
		wDrawY = 0;

		// ������ ã��
		for (int row = 0; row < image_output.rows; row++)
		{
			for (int col = 0; col < image_output.cols; col++)
			{
				index = ((row * image_output.cols) + col) * image_output.channels();
				if (image_output.data[index + 2] < 50 && image_output.data[index + 1] < 50 && image_output.data[index] < 50) // ������
				{
					cv::circle(image_output, cv::Point(col, row), 2, cv::Scalar(100, 200, 100), 1);
					bCount++;
					bDrawX += col;
					bDrawY += row;
				}
				else if (image_output.data[index + 2] > 240 && image_output.data[index + 1] > 240 && image_output.data[index] > 240) // ���
				{
					cv::circle(image_output, cv::Point(col, row), 2, cv::Scalar(100, 100, 200), 1);
					wCount++;
					wDrawX += col;
					wDrawY += row;
				}
			}
		}

		// ��ġ ��� ���
		if (bCount > 0 && bCount < 100)
		{
			bDrawX /= bCount;
			bDrawY /= bCount;
			cv::circle(image_output, cv::Point(bDrawX, bDrawY), 20, cv::Scalar(200, 200, 255), 2);
		}
		if (wCount > 0 && wCount < 100)
		{
			wDrawX /= wCount;
			wDrawY /= wCount;
			cv::circle(image_output, cv::Point(wDrawX, wDrawY), 20, cv::Scalar(255, 200, 200), 2);
		}


		// �̹��� ���
		cv::imshow("ī�޶�", image);
		cv::imshow("ó�����", image_output);

		// ������
		char keyinput = cv::waitKey(30);
		if (keyinput == 27)
		{
			break;
		}
	}

	camera.release();

	return 0;
}