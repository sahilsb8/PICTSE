#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAIN_EXIT 1
#define MAIN_RESET 2
#define RESISTOR_VALUE_COLOUR_3 3
#define MAIN_HELP 4
#define RESISTOR_COLOUR_CODE_3 5

typedef struct Queue
{
    int data[20];
	int front,rear;
}Queue;
Queue p;

void init(Queue *p)
{
	p->front = -1;
	p->rear = -1;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void AddControls(HWND);
float divide(float res);
int multiplier(int i);
void colorband4(int res,int tol);
int dequeue(Queue *q);
int digits(int resistance);
void enqueue(Queue *s,int ele);
void colorband410(int res, int tol);

int multi, cross;

const char* color[12] = {"Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Grey", "White", "Gold", "Silver"};
const char*toler[9] = {"Brown", "Red", "Green", "Blue", "Voilet", "Grey", "Gold", "Silver", "No color"};

HMENU hMenu;
HWND hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6, hOut, hOut1;

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd;	   /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg;	   /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Resistor Colour code convertor", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, /* x */
						  CW_USEDEFAULT, /* y */
						  1280,			 /* width */
						  480,			 /* height */
						  NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{							/* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg);	/* Send it to WndProc */
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case MAIN_EXIT:
		{
			DestroyWindow(hwnd);
			MessageBeep(MB_ICONWARNING);
			break;
		}
		case MAIN_RESET:
		{
			MessageBeep(MB_ICONWARNING);
			SetWindowText(hOut, "Output will be here...");
			SetWindowText(hOut1, "Output will be here...");
			SetWindowText(hEdit1, NULL);
			SetWindowText(hEdit2, NULL);
			SetWindowText(hEdit3, NULL);
			SetWindowText(hEdit4, NULL);
			SetWindowText(hEdit5, NULL);
			SetWindowText(hEdit6, NULL);
			break;
		}
		case RESISTOR_VALUE_COLOUR_3:
		{
			char band1Val[100], band2Val[100], band3Val[100], band4Val[100];
			GetWindowText(hEdit1, band1Val, 100);
			GetWindowText(hEdit2, band2Val, 100);
			GetWindowText(hEdit3, band3Val, 100);
			GetWindowText(hEdit4, band4Val, 100);
			int band1ValInt = atoi(band1Val);
			int band2ValInt = atoi(band2Val);
			int band3ValInt = atoi(band3Val);
			int band4ValInt = atoi(band4Val);
			//SetWindowText(hOut, band1Val);
			//final = band3(band1Val, band2Val, band3Val);
			int temp = band3Val;
			float band3ValF = band3ValInt;
			float total;
			if(band1ValInt<=9 && band2ValInt<=9 && (band3ValF<=9 || (band3ValF==10 || band3ValF==11)))
			{
				if(band3ValF<10)
				{
					band3ValF = multiplier(band3ValF);
				}
				else if(band3ValF==10)
				{
					band3ValF=0.1;
				}
				else if(band3ValF==11)
				{
					band3ValF=0.01;
				}
				total = ((band1ValInt * 10) + band2ValInt) * band3ValF;
			}
			else
			{
				total = -1;
			}
			char fin[20];
			//itoa(total, fin, 10);
			float fin1 = divide(total);
			gcvt(fin1, 5, fin);
			if(multi == 1)
			{
				strcat(fin, " Ohm");
			}
			else if(multi == 2)
			{
				strcat(fin, " KOhm");
			}
			else if(multi == 3)
			{
				strcat(fin, " MOhm");
			}
			else if(multi == 4)
			{
				strcat(fin, " GOhm");
			}
			switch(band4ValInt)
			{
				case 1: {
					strcat(fin, " ± 1%");
					break;
				}
				case 2: {
					strcat(fin, " ± 2%");
					break;
				}
				case 5: {
					strcat(fin, " ± 0.5%");
					break;
				}
				case 6: {
					strcat(fin, " ± 0.25%");
					break;
				}
				case 7: {
					strcat(fin, " ± 0.10%");
					break;
				}
				case 8: {
					strcat(fin, " ± 0.05%");
					break;
				}
				case 10: {
					strcat(fin, " ± 5%");
					break;
				}
				case 11: {
					strcat(fin, " ± 10%");
					break;
				}
				default: {
					total = -1;
					break;
				}
			}
			if(total == -1)
			{
				SetWindowText(hOut, "INVALID COLOUR CODED RESISTOR!");
			}
			else
			{
				SetWindowText(hOut, fin);
			}
			break;
		}
		case RESISTOR_COLOUR_CODE_3:
		{
			init(&p);
			char resval[100], restol[100];
			GetWindowText(hEdit5, resval, 100);
			GetWindowText(hEdit6, restol, 100);
			int resvalInt = atoi(resval);
			int restolInt = atoi(restol);
			if(restolInt > 9 | restolInt < 1 | resvalInt < 0)
			{
				SetWindowText(hOut1, "INVALID value and/or code, TRY AGAIN!");
			}
			else
			{
				digits(resvalInt);
				cross = 0;
				if(resvalInt >= 100)
				{
					colorband4(resvalInt, restolInt);
				}
				else
				{
					colorband410(resvalInt, restolInt);
				}
			}
			break;
		}
		case MAIN_HELP: 
		{
			MessageBoxW(hwnd, L"Enter the code corresponding to the respective colour or respective tolerance as shown at the top of the window. Then press the \"Get Band colours\" button or \"Get resistor value\" to generate the band colours or resistor value respectively. press the reset button to reset the program!", L"Help", MB_ICONQUESTION | MB_OK);
			break;
		}
		}
		break;
	}
	case WM_CREATE:
	{
		AddMenus(hwnd);
		AddControls(hwnd);
		break;
	}
	/* Upon destruction, tell the main thread to stop */
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	/* All other messages (a lot of them) are processed using default procedures */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void AddMenus(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu1 = CreateMenu();
	HMENU hSubMenu2 = CreateMenu();

	AppendMenu(hSubMenu1, MF_STRING, NULL, "3 Bands (E6 Series)");
	AppendMenu(hSubMenu1, MF_STRING, NULL, "4 Bands (E12 Series)");
	AppendMenu(hSubMenu1, MF_STRING, NULL, "5 Bands (E48 Series)");
	//AppendMenu(hSubMenu1, MF_STRING, NULL, "6 Bands (E96 Series)");

	AppendMenu(hSubMenu2, MF_STRING, NULL, "3 Bands (E6 Series)");
	AppendMenu(hSubMenu2, MF_STRING, NULL, "4 Bands (E12 Series)");
	AppendMenu(hSubMenu2, MF_STRING, NULL, "5 Bands (E48 Series)");
	//AppendMenu(hSubMenu2, MF_STRING, NULL, "6 Bands (E96 Series)");

	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu1, "Resistor value to colour code");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu2, "Resistor colour code to value");

	//AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL); --> separator if needed

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "Type");
	AppendMenu(hMenu, MF_STRING, MAIN_RESET, "Reset");
	AppendMenu(hMenu, MF_STRING, MAIN_HELP, "Help");
	AppendMenu(hMenu, MF_STRING, MAIN_EXIT, "Exit");
	SetMenu(hwnd, hMenu);
}

void AddControls(HWND hwnd)
{
	CreateWindowW(L"Static", L"Black -->0 | Brown-->1 | Red-->2 | Orange-->3 | Yellow-->4 | Green-->5 | Blue-->6 | Violet-->7 | Grey--> 8 | White--> 9 | Gold-->10 | Silver-->11", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 100, 10, 410, 90, hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Enter band 1 colour code here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 100, 110, 300, 20, hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Enter band 2 colour code here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 100, 140, 300, 20, hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Enter band 3 colour code here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 100, 170, 300, 20, hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Enter band 4 colour code here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 100, 200, 300, 20, hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"MADE BY: Atharv Dhup | Krishna Chidrawar | Pratik Bhil | Sahil Borkar for DS PBL Project...", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 355, 350, 570, 40, hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"Static", L"Enter Resistor value here:\n(Integer value only!)", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 770, 110, 300, 50, hwnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Enter Tolerance code here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 770, 170, 300, 50, hwnd, NULL, NULL, NULL);
	
	hEdit1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 410, 110, 100, 20, hwnd, NULL, NULL, NULL);
	hEdit2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 410, 140, 100, 20, hwnd, NULL, NULL, NULL);
	hEdit3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 410, 170, 100, 20, hwnd, NULL, NULL, NULL);
	hEdit4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 410, 200, 100, 20, hwnd, NULL, NULL, NULL);
	
	hEdit5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 1080, 110, 100, 50, hwnd, NULL, NULL, NULL);
	hEdit6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 1080, 170, 100, 50, hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"Button", L"Get resistor value", WS_VISIBLE | WS_CHILD, 100, 230, 150, 20, hwnd, (HMENU)RESISTOR_VALUE_COLOUR_3, NULL, NULL);
	CreateWindowW(L"Button", L"Get Band colours", WS_VISIBLE | WS_CHILD, 770, 230, 150, 20, hwnd, (HMENU)RESISTOR_COLOUR_CODE_3, NULL, NULL);
	
	hOut = CreateWindowW(L"Edit", L"Output will be here...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 100, 260, 410, 40, hwnd, NULL, NULL, NULL);
	hOut1 = CreateWindowW(L"Edit", L"Output will be here...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 770, 260, 410, 40, hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"Static", L"1%-->1 | 2%-->2 | 0.5%-->3 | 0.25%-->4 | 0.10%-->5 | 0.05%-->6 | 5%-->7 | 10%-->8 | 20%-->9", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 770, 10, 410, 90, hwnd, NULL, NULL, NULL);
	
}

int multiplier(int i)
{
	int p, t;
	t = 1;
	for(p=0;p<i;p++)
	{
		t=t*10;
	}
	return(t);
}

float divide(float res)
{
	if(res <= 999)
	{
		multi = 1;
		return res;
	}
	else if(res <= 999999)
	{
		multi = 2;
		return res/1000;
	}
	else if(res <= 999999999)
	{
		multi = 3;
		return res/1000000;
	}
	else
	{
		multi = 4;
		return res/1000000000;
	}
}

void colorband4(int res,int tol)
{
	char finstr[100];
	int first,second;
	int multip;
	first = dequeue(&p); 									
	second = dequeue(&p);									
	int third;
	third = dequeue(&p);							
	multip = p.rear + 1;
	int temp;
	temp = multip;							
	if(third >= 5)
	{
		multip++;
		second++; 								
		if(second == 10)     					
		{		
			multip = temp;							
			first++;
			second = 0;
			multip++;
			if(first == 10)
			{
				multip = temp;
				first = 1;
				multip = multip + 2;	
			}
		}
	}
	else
	{
		multip++;
	}
	strcpy(finstr,color[first]);
	strcat(finstr, ", ");
	strcat(finstr, color[second]);
	strcat(finstr, ", ");
	strcat(finstr, color[multip - cross]);
	strcat(finstr, ", ");
	strcat(finstr, toler[tol-1]);
	SetWindowText(hOut1, finstr);
}

int dequeue(Queue *q)
{
	int x;
		if(q->front == q->rear)
		{
			x = q->data[q->front];
			q->front=q->rear=-1;
		}
		else
		{
			x = q->data[q->front];
		    int i;
		    for(i = q->front+1; i <= q->rear; i++)
		    {
		    	q->data[i-1] = q->data[i];
			}
			q->rear--;
		}
		return x;	
}

int digits(int resistance)
{
	int storevalue[20];
	int i = 0;
	int j;	
	while(resistance != 0)
	{
		j = resistance % 10;
		resistance = resistance / 10;
		storevalue[i] = j;
		i++;
	}
	i--;		
	for(;i>=0;)
	{	
		enqueue(&p, storevalue[i]);
		i--;		
	}
}

void enqueue(Queue *s,int ele)
{
	if(s->front==-1)
	{
    	s->front++;			
	}
	s->rear++; 
	s->data[s->rear]=ele;
}

void colorband410(int res, int tol)
{
	char finstr[50];
	if(res >= 10)
	{
		strcpy(finstr, color[res / 10]);
		strcat(finstr, ", ");
		strcat(finstr, color[res % 10]);
		strcat(finstr, ", ");
		strcat(finstr, "Black");
		strcat(finstr, ", ");
		strcat(finstr, toler[tol-1]);
		SetWindowText(hOut1, finstr);//
	}
	else if(res >= 0)
	{
		strcpy(finstr, "Black");
		strcat(finstr, ", ");
		strcat(finstr, color[res]);
		strcat(finstr, ", ");
		strcat(finstr, "Black");
		strcat(finstr, ", ");
		strcat(finstr, toler[tol-1]);
		SetWindowText(hOut1, finstr);
	}
}

