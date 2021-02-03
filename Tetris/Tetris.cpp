#pragma region ��Ϸͷ�ļ�
#include "Tetris.h"
#pragma endregion

#pragma region ��ʼ������
void Init()
{
	#pragma region ���������ʼ��
	Tetris.InitCurrent_j = 27;//��ǰ�����ʼ��ʱ�����¸��� ��ֵ
	Tetris.InitCurrent_i = 5;//��ǰ�����ʼ��ʱ�����¸��� ��ֵ
	Tetris.InitCurrent_x = 0;//��ǰ�����ʼ��ʱ�����¸��� ���½�����
	Tetris.InitCurrent_y = 0;//��ǰ�����ʼ��ʱ�����¸��� ���½�����

	Tetris.Current_Number = 0;//��ǰ���� ���
	Tetris.Current_Form = 0;//��ǰ���� ��״

	Tetris.Current_j = 0;//��ǰ���������¸��� ��ֵ
	Tetris.Current_i = 0;//��ǰ���������¸��� ��ֵ
	Tetris.Current_x = 0;//��ǰ���������¸��� ���½�����
	Tetris.Current_y = 0;//��ǰ���������¸��� ���½�����
	#pragma endregion

	WindowPosition_X = 100,WindowPosition_Y = 50;//����λ�ó�ʼ��
	
	Tetris.Current_Number = rand()%7;//��һ������

	for(int j=0;j<33;j++)//��Ϸ��������
	{
		for(int i=0;i<12;i++)
			Grid[j][i] = 0;
		Grid[j][12] = 1;//�ұ߽�����
		Grid[j][13] = 1;//�ұ߽�����
		Grid[j][14] = 1;//�ұ߽�����
	}

	glClearColor(127,127,127,1.0);//���ڱ���ɫ
	glMatrixMode(GL_PROJECTION);//����ģʽ����
	gluOrtho2D(WindowPosition_X-2,WindowPosition_X+View_Width+101,WindowPosition_Y-2,WindowPosition_Y+View_Height+101);	//����߽�����
	glViewport(WindowPosition_X-2,WindowPosition_Y-2,View_Width+103,View_Height+103);//������ʾ����
}
#pragma endregion

#pragma region ��Ϸ��Ϣ��ʾ
void DrawInfo()
{
	#pragma region ����
	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Header[10]="Tetris";//��Ϸ����
	glRasterPos2i(WindowPosition_X+View_Width-140,WindowPosition_Y+View_Height+20);
	for (int i=0;Text_Header[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Text_Header[i]);
	#pragma endregion

	#pragma region ��һ������ʾ
	char Text_Next[10]="Next:";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-20);
	for (int i=0;Text_Next[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Next[i]);
	DrawNextTetris(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-110);
	#pragma endregion

	#pragma region ��Ϸ����
	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Help_F1[30]="Press F1 to Pause/Continue";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-140);
	for (int i=0;Text_Help_F1[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Help_F1[i]);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Help_F2[30]="Press F2 to add Level";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-170);
	for (int i=0;Text_Help_F2[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Help_F2[i]);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Help_F3[30]="Press F3 to start Death Mode";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-200);
	for (int i=0;Text_Help_F3[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Help_F3[i]);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Help_Up[30]="Press Up to rotate";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-250);
	for (int i=0;Text_Help_Up[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Help_Up[i]);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Help_Left[30]="Press Left to move left";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-280);
	for (int i=0;Text_Help_Left[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Help_Left[i]);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Help_Right[30]="Press Right to move right";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-310);
	for (int i=0;Text_Help_Right[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Help_Right[i]);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Help_Down[30]="Press Down to move down";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-340);
	for (int i=0;Text_Help_Down[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Help_Down[i]);
	#pragma endregion

	#pragma region �ѶȻ��������Ϣ
	glColor4f(0.0f,0.0f,1.0f,1.0f);
	char Text_Point[20]="Point:";
	char Point_Char[10];
	_itoa_s(Point,Point_Char,10);
	strcat_s(Text_Point,Point_Char);
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-390);
	for (int i=0;Text_Point[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Point[i]);

	char Text_Total[20]="Total:";
	char Total_Char[10];
	_itoa_s(Count*100,Total_Char,10);
	strcat_s(Text_Total,Total_Char);
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-420);
	for (int i=0;Text_Total[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Total[i]);

	char Text_Score[20]="Score:";
	char Score_Char[10];
	_itoa_s(Score,Score_Char,10);
	strcat_s(Text_Score,Score_Char);
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-450);
	for (int i=0;Text_Score[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Score[i]);

	char Text_Level[20]="Level:";
	char Level_Char[10];
	char Level_Max[10]="Max";
	char Death_Mode[20]="Death Mode";
	_itoa_s(Level,Level_Char,10);
	if(!DeathMode)
		if(Level < 10)		
		{
			_itoa_s(Level,Level_Char,10);
			strcat_s(Text_Level,Level_Char);
		}
		else
			strcat_s(Text_Level,Level_Max);
	else
		strcat_s(Text_Level,Death_Mode);
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-480);
	for (int i=0;Text_Level[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Level[i]);

	char Text_Speed[20]="Speed:";
	char Speed_Char[10];
	_itoa_s(Speed[Level],Speed_Char,10);
	strcat_s(Text_Speed,Speed_Char);
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-510);
	for (int i=0;Text_Speed[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Speed[i]);
	#pragma endregion

	#pragma region ������Ϣ
	char Text_Name[30]="Programmed by Chong Fei";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-560);
	for (int i=0;Text_Name[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Name[i]);

	char Text_Rights[30]="All Rights reserved!";
	glRasterPos2i(WindowPosition_X+View_Width+16,WindowPosition_Y+View_Height-590);
	for (int i=0;Text_Rights[i];i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Text_Rights[i]);
	#pragma endregion
}
#pragma endregion

#pragma region ����С����
void DrawSquare(GLint x,GLint y)
{
	if(y < WindowPosition_Y+View_Height)//����3��ͼ��Խ��
	{
		glBegin(GL_QUADS);
		{
			glVertex2i(x,y);
			glVertex2i(x+19,y);
			glVertex2i(x+19,y+19);
			glVertex2i(x,y+19);
		}
		glEnd();
	}
}
#pragma endregion

#pragma region �����·���
void DrawCurrentTetris(int x,int y)
{
	glPushMatrix();
	glColor3f(0.0,0.6,0.0);
	for(int k=0;k<5;k++)
		for(int l=0;l<6;l++)
		{
			if(TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 1)
				DrawSquare(x+20*(l-1),y+20*(k-1));
		}
	glPopMatrix();
}
#pragma endregion

#pragma region ������һ������
void DrawNextTetris(int x,int y)
{
	glPushMatrix();
	glColor3f(0.0,0.6,0.0);
	for(int k=0;k<5;k++)
		for(int l=0;l<6;l++)
		{
			if(TetrisShape[Tetris.Next_Number][0][k][l] == 1)
				DrawSquare(x+20*(l-1),y+20*(k-1));
		}
	glPopMatrix();
}
#pragma endregion

#pragma region �������ۻ�����
void DrawTetris(int x,int y)//�������ۻ��ķ���
{
	glPushMatrix();

	if(Game_Over)//Game_Overʱ�����Ϊ��ɫ
		glColor3f(0.5,0.5,0.5);
	else
		glColor3f(0.0,0.6,0.0);

	for(int i=0;i<12;i++)
		for(int j=0;j<30;j++)
		{
			static int temp = 1;//��ִֻ֤��һ�Σ��õ������ʼ��ʱ������
			if(temp==1 && i==Tetris.InitCurrent_i && j==Tetris.InitCurrent_j)
			{
				Tetris.InitCurrent_x = x+20*i;
				Tetris.InitCurrent_y = y+20*j;
				temp = 0;
			}
			if(Grid[j][i] == 1)
				DrawSquare(x+20*i,y+20*j);
		}
	
	if(Game_Over)
		GameOver();

	glPopMatrix();
}
#pragma endregion

#pragma region ��鷽���Ƿ�����ĳ�����ƶ�
bool TetrisCanMove(int direction)
{
	switch(direction)
	{
	case DOWN://�ܷ������ƶ�
		for(int k=0;k<5;k++)
			for(int l=0;l<6;l++)
			{
				if(TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 2 || TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 5 || TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 6)
					if(Tetris.Current_j == 0 || Grid[Tetris.Current_j+k-1][Tetris.Current_i+l-1] == 1)
						return 0;
			}
		break;
	case LEFT://�ܷ������ƶ�
		for(int k=0;k<5;k++)
			for(int l=0;l<6;l++)
			{
				if(TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 3 || TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 5)
					if((Tetris.Current_Number != 3 && Tetris.Current_i == 0) || (Tetris.Current_Number == 3 && Tetris.Current_i == -1) || Grid[Tetris.Current_j+k-1][Tetris.Current_i+l-1] == 1)//���ͼ��3�������������Դ�
						return 0;
			}
		break;
	case RIGHT://�ܷ������ƶ�
		for(int k=0;k<5;k++)
			for(int l=0;l<6;l++)
			{
				if(TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 4 || TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 6)
					if((Tetris.Current_Number != 3 && Tetris.Current_i+l-2 == 11) || (Tetris.Current_Number == 3 && Tetris.Current_i-1 == 11) || Grid[Tetris.Current_j+k-1][Tetris.Current_i+l-1] == 1)//���ͼ��3�������������Դ�
						return 0;
			}
		break;
	}
	return 1;
}
#pragma endregion

#pragma region ���������ƶ�
void TetrisMovement_Down()
{
	if(!Pause)
	{
		if(TetrisCanMove(DOWN))
		{
			Tetris.Current_j --;
			Tetris.Current_y -= 20;
			LayerCut();
			glutPostRedisplay();
		}
		else if(Game_Over != 1)//����Ѿ����ף���ı����ۻ����飬�������·���
		{
			for(int k=0;k<5;k++)
				for(int l=0;l<6;l++)
				{
					if(TetrisShape[Tetris.Current_Number][Tetris.Current_Form][k][l] == 1)
						Grid[Tetris.Current_j+k-1][Tetris.Current_i+l-1] = 1;
				}
			NewTetrisNeeded = 1;
			LayerCut();
			Count++;
			glutPostRedisplay();
		}
	}
}
#pragma endregion

#pragma region ���������ƶ�
void TetrisMovement_Left()
{
	if(TetrisCanMove(LEFT))
	{
		Tetris.Current_i --;
		Tetris.Current_x -= 20;
		
		glutPostRedisplay();
	}
}
#pragma endregion

#pragma region ���������ƶ�
void TetrisMovement_Right()
{
	if(TetrisCanMove(RIGHT))
	{
		Tetris.Current_i ++;
		Tetris.Current_x += 20;
		
		glutPostRedisplay();
	}
}
#pragma endregion

#pragma region ������ת
void TetrisRotate()
{
	int CurrentTetris_NextForm = (Tetris.Current_Form+1)%4;//��һ��̬����

	for(int k=0;k<5;k++)
		for(int l=0;l<6;l++)
		{
			if(TetrisShape[Tetris.Current_Number][CurrentTetris_NextForm][k][l] == 1)
				if(Grid[Tetris.Current_j+k-1][Tetris.Current_i+l-1] == 1)
					return;
		}
	Tetris.Current_Form = CurrentTetris_NextForm;
	glutPostRedisplay();
}
#pragma endregion

#pragma region �����Զ�����
void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
	TetrisMovement_Down();
}   
#pragma endregion

#pragma region ���������������
void LayerCut()
{
	int Num;//һ��������������
	Num = 0;
	int Line;

	Line = (Point - 110000) / 2000;
	if(Line > 16)
		Line = 16;//�Ѷ����ã�11w��֮��ÿ2000�֣���һ�п������������13�У������������3�У�
	for(int j = Line;j<30;j++)//���������������
	{
		int temp = 0;
		for(int i = 0;i<12;i++)
		{
			if(Grid[j][i] == 1)
				temp++;
		}

		if(temp == 12)
		{
			for(int k=j;k<30;k++)
				for(int l=0;l<12;l++)
					Grid[k][l] = Grid[k+1][l];
			j--;
			Num++;
		}
	}

	//���ֻ�ü���
	switch(Num)
	{
	    case 1:
			Point += 100;
			break;
		case 2:
			Point += 300;
			break;
		case 3:
			Point += 900;
			break;
		case 4:
			Point += 1600;
			break;
	}

	if(!DeathMode)
	{
		if(Count)
			Score = (float)Point/((float)Count*100)*(1000+(float)Speed[10-Level])/2000*(float)Point;
	}
	else
		if(Count)
			Score = (float)Point/((float)Count*100) * 1.5 * Point;
	
	//��Ϸ�ؿ����㣬10000��һ��
	if(!DeathMode)
	{
		Level = Point/10000 + Level_Add;
		if(Level > 10)
			Level = 10;
	}

	//��Ϸ�ٶȸ���
	if(!DeathMode)
	{
		if(Level > Level_Old)
		{
			Level_Old = Level;
			KillTimer(hWnd,Timer);
			Timer = SetTimer(NULL,1,Speed[Level],(TIMERPROC)TimerProc);//��Ϸ�ٶ�����
		}
	}
}
#pragma endregion

#pragma region ִ�л�ͼ����
void Draw()
{
	//������Ϸ�������
	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2i(WindowPosition_X-1,WindowPosition_Y+View_Height);
		glVertex2i(WindowPosition_X-1,WindowPosition_Y-2);
		glVertex2i(WindowPosition_X+View_Width+1,WindowPosition_Y-2);
		glVertex2i(WindowPosition_X+View_Width+1,WindowPosition_Y+View_Height);
	}
	glEnd();
	glPopMatrix();

	//������һ�����������
	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2i(WindowPosition_X+View_Width+15,WindowPosition_Y+View_Height-112);
		glVertex2i(WindowPosition_X+View_Width+77,WindowPosition_Y+View_Height-112);
		glVertex2i(WindowPosition_X+View_Width+77,WindowPosition_Y+View_Height-30);
		glVertex2i(WindowPosition_X+View_Width+15,WindowPosition_Y+View_Height-30);
	}
	glEnd();
	glPopMatrix();

	//Game_Over�ж�
	for(int i=0;i<12;i++)
	{
		if(i < 5 || i > 7)
		{
			if(Grid[29][i] == 1)
			{
				Game_Over = 1;
				KillTimer(hWnd,Timer);
				break;
			}
		}
		else
		{
			if(Grid[27][i] == 1)
			{
				Game_Over = 1;
				KillTimer(hWnd,Timer);
				break;
			}
		}
	}

	//�������ۻ�����
	DrawTetris(WindowPosition_X,WindowPosition_Y);

	//�����·���
	if(!Game_Over)
	{
		if(NewTetrisNeeded)
		{
			Tetris.Current_Form = 0;
			Tetris.Current_Number = Tetris.Next_Number;
			Tetris.Next_Number = rand()%7;

			Tetris.Current_j = Tetris.InitCurrent_j;
			Tetris.Current_i = Tetris.InitCurrent_i;

			Tetris.Current_x = Tetris.InitCurrent_x;
			Tetris.Current_y = Tetris.InitCurrent_y;
			NewTetrisNeeded = 0;
		}
		DrawCurrentTetris(Tetris.Current_x,Tetris.Current_y);
	}

	//��ʾ��Ϸ��Ϣ
	DrawInfo();
}
#pragma endregion

#pragma region ���ⰴ����Ӧ����
void KeyboardFunc(GLint SpecialKey,GLint Mouse_X,GLint Mouse_Y)
{
	switch(SpecialKey)
	{
	case GLUT_KEY_F1://��ͣ/������Ϸ
		switch(Pause)
		{
		case 0://��Ϸ��ͣ
			KillTimer(hWnd,Timer);
			Pause = 1;
			break;
		case 1://������Ϸ
			KillTimer(hWnd,Timer);
			Timer = SetTimer(NULL,1,Speed[Level],(TIMERPROC)TimerProc);//��Ϸ�ٶ�����
			Pause = 0;
			break;
		}
		break;
	case GLUT_KEY_F2://�ؿ�+1
		if(!Pause && !DeathMode)
		{
			Level ++;
			Level_Add ++;
			KillTimer(hWnd,Timer);
			Timer = SetTimer(NULL,1,Speed[Level],(TIMERPROC)TimerProc);//��Ϸ�ٶ�����
			Pause = 0;
			break;
		}
		break;
	case GLUT_KEY_F3://��������ģʽ
		if(!DeathMode)
		{
			DeathMode = 1;
			Score = 0;
			Count = 0;
			Point = 0;
			Level = 11;
			for(int j=0;j<33;j++)
			{
				for(int i=0;i<12;i++)
					Grid[j][i] = 0;
				Grid[j][12] = 1;
				Grid[j][13] = 1;
				Grid[j][14] = 1;
			}
			KillTimer(hWnd,Timer);
			Timer = SetTimer(NULL,1,Speed[Level],(TIMERPROC)TimerProc);//��Ϸ�ٶ�����
		}
		break;
	case GLUT_KEY_LEFT:
		if(!Pause)
			TetrisMovement_Left();
		break;
	case GLUT_KEY_RIGHT:
		if(!Pause)
			TetrisMovement_Right();
		break;
	case GLUT_KEY_UP:
		if(!Pause)
			TetrisRotate();
		break;
	case GLUT_KEY_DOWN:
		if(!Pause)
			TetrisMovement_Down();
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region ��Ϸ���к���
void GameDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Draw();

	glFlush();
}
#pragma endregion

#pragma region ��Ϸʧ�ܺ���
void GameOver()
{
	//GameOver��Ϣ
	glColor4f(1.0f,0.0f,0.0f,1.0f);
	char Text_Gameinfo[20]="Game Over!";
	glRasterPos2i(WindowPosition_X+View_Width-170,WindowPosition_Y+View_Height+50);
	for (int i=0;Text_Gameinfo[i];i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Text_Gameinfo[i]);

	//������ʾ����
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	{
		glVertex2i(WindowPosition_X,WindowPosition_Y+View_Height/2);
		glVertex2i(WindowPosition_X+View_Width,WindowPosition_Y+View_Height/2);
		glVertex2i(WindowPosition_X+View_Width,WindowPosition_Y+View_Height/2+100);
		glVertex2i(WindowPosition_X,WindowPosition_Y+View_Height/2+100);
	}
	glEnd();

	//������ʾ����߽���
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2i(WindowPosition_X+1,WindowPosition_Y+View_Height/2);
		glVertex2i(WindowPosition_X+View_Width-1,WindowPosition_Y+View_Height/2);
		glVertex2i(WindowPosition_X+View_Width-1,WindowPosition_Y+View_Height/2+100);
		glVertex2i(WindowPosition_X+1,WindowPosition_Y+View_Height/2+100);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		glVertex2i(WindowPosition_X+2,WindowPosition_Y+View_Height/2+1);
		glVertex2i(WindowPosition_X+View_Width-2,WindowPosition_Y+View_Height/2+1);
		glVertex2i(WindowPosition_X+View_Width-2,WindowPosition_Y+View_Height/2+99);
		glVertex2i(WindowPosition_X+2,WindowPosition_Y+View_Height/2+99);
	}
	glEnd();

	//�÷���ʾ
	glColor4f(1.0f,0.0f,1.0f,1.0f);
	char Text_Gameinfo1[30]="Your final score is";
	glRasterPos2i(WindowPosition_X+32,WindowPosition_Y+View_Height/2+60);
	for (int i=0;Text_Gameinfo1[i];i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Text_Gameinfo1[i]);

	char Score_Char[10];
	_itoa_s(Score,Score_Char,10);
	glRasterPos2i(WindowPosition_X+22+(200-strlen(Score_Char)*10)/2,WindowPosition_Y+View_Height/2+25);
	for (int i=0;Score_Char[i];i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Score_Char[i]);
}
#pragma endregion

#pragma region ����ͶӰ����
void WindowReshape(GLint newWidth,GLint newHeight)
{
}
#pragma endregion

#pragma region ��Ϸ������
void main(int argc,char** argv)
{
	#pragma region glut��ʼ��
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(Window_Width,Window_Height);
	glutCreateWindow("����˹���� Version 1.41");
	#pragma endregion

	srand((unsigned)time( NULL ));//������ӳ�ʼ��

	#pragma region ��Ϸ��������
	Init();
	glutDisplayFunc(GameDisplay);
	glutReshapeFunc(WindowReshape);
	glutSpecialFunc(KeyboardFunc);
	glutMainLoop();
	#pragma endregion
}
#pragma endregion