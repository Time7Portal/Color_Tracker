#include <iostream>
#include <opencv2\opencv.hpp>


int main()
{
	// 임계값
	int thres = 64;
	int index = 0;
	int bCount = 0;
	int wCount = 0;
	int bDrawX = 0;
	int bDrawY = 0;
	int wDrawX = 0;
	int wDrawY = 0;

	// 이미지 정의
	cv::Mat image;
	cv::Mat image_gray;
	cv::Mat image_output;

	// 카메라 정의
	cv::VideoCapture camera;
	// camera.open(0); // 웹캠
	camera.open("E:\\프로젝트\\OpenCV\\BobRoss.mp4"); // 샘플 동영상
	if (!camera.isOpened())
	{
		return 0;
	}

	// 윈도우 정의
	cv::namedWindow("카메라", 1);
	cv::namedWindow("처리결과", 1);

	// 트랙바 넣기
	cv::createTrackbar("강도", "처리결과", &thres, 64, NULL);

	// 실시간 출력
	while (1)
	{
		// 카메라 이미지 복사
		camera >> image;

		// 좌우반전
		//cv::flip(image, image, 1);

		// 이미지 해상도 축소
		cv::resize(image, image_output, cv::Size(640, 480));

		// 이진화
		//cv::cvtColor(image_output, image_gray, CV_RGB2GRAY);
		//cv::threshold(image_gray, image_output, (thres * 2), 255, CV_THRESH_BINARY);

		// 탐색값 초기화
		bCount = 0;
		bDrawX = 0;
		bDrawY = 0;
		wCount = 0;
		wDrawX = 0;
		wDrawY = 0;

		// 빨간색 찾기
		for (int row = 0; row < image_output.rows; row++)
		{
			for (int col = 0; col < image_output.cols; col++)
			{
				index = ((row * image_output.cols) + col) * image_output.channels();
				if (image_output.data[index + 2] < 50 && image_output.data[index + 1] < 50 && image_output.data[index] < 50) // 검은색
				{
					cv::circle(image_output, cv::Point(col, row), 2, cv::Scalar(100, 200, 100), 1);
					bCount++;
					bDrawX += col;
					bDrawY += row;
				}
				else if (image_output.data[index + 2] > 240 && image_output.data[index + 1] > 240 && image_output.data[index] > 240) // 흰색
				{
					cv::circle(image_output, cv::Point(col, row), 2, cv::Scalar(100, 100, 200), 1);
					wCount++;
					wDrawX += col;
					wDrawY += row;
				}
			}
		}

		// 위치 평균 계산
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


		// 이미지 출력
		cv::imshow("카메라", image);
		cv::imshow("처리결과", image_output);

		// 딜레이
		char keyinput = cv::waitKey(30);
		if (keyinput == 27)
		{
			break;
		}
	}

	camera.release();

	return 0;
}