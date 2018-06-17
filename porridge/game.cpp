#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib,"winmm.lib")
#include<windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include<algorithm>
#include<string.h>
#include<vector>
#include<cstdio>
#include<time.h>
#include"1.h"
using namespace std;
int FUCK=0,EAT=0,clsun=0;
HINSTANCE hInst;
HBITMAP b[30][30],bit[20][30],btb[20][30],c[20][40],a[10][20],d[10][20],e[20][20];
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
BITMAP  bm[30][30],bp,bmtb[20][30],cm[20][40],am[10][20];
HRGN hrgn[20][30];
RECT rect;
PAINTSTRUCT ps ; 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);
int pnum[10],znum[10];
int xx[4]={200,300,400,500};
int yy[3]={200,300,400};
int zflag[10]={1,1,3,1,3,1,1,3,3,1};
int zombiey[20]={140,340,440,40,240,340,340,40,140,440,440,240,40,140,240,40,440,140,40,240};
int zombiey2[20]={140,340,280,240,160,300,120,400,70,180,260,320,120,90,430,360,200,300,150,370};
struct node{
	int x,y,i,j,marks,have,sunj,limit,PAINT,repeater,life,time;
}map[10][10];		
struct abc{
	int x,y;
}plant[30];
struct haha{
	int x,y,plant,bright,price,cd,time;
	bool isclick;
}tubiao[15];
struct hehe{
	int x,y,outx,outy;
	bool inback;
}cz;
struct hoho{
	int x,y;
}czback;
struct flag{
	int ANFANG,i;
}AF;
struct sn{
	int x,y,num;
}sunnum;
struct ssun{
	int x,y,j,endy;
}sun;
struct wd{
	int x,y,flag,mark,i,j;
	bool operator< (const wd &a)  const{
        return x<a.x;
    }
}hit;
struct dead{
	int x,y,flag,i,j,life,v,stata,headj,slow,attack,t;
	bool operator< (const dead &a)  const{
		if(y!=a.y)
			return y<a.y;
		else
			return x<a.x;
    }
}zombie;
bool cmp(dead a,dead b){
	if(a.y!=b.y)
		return a.y<b.y;
	else
		return a.x>b.x;
}
struct man{
	int x,y,flag,j;
}dava;
struct h{
	int x,y,j;
}hand;
struct aaa{
	int x,y,v;
}background;
struct sss{
	int x,y,j,vx,vy;
}ssun;
vector<wd>vec;
vector<wd>::iterator it;
vector<dead>Zombie;
vector<dead>::iterator it1;
vector<sss>sunsun;
vector<sss>::iterator it2;
int mousex,mousey,movex,movey,which=0,zbj=1,stepi=0,suntime,tt,zombiet,fuck,z;
int CLICK=0,MARKAF=0,K=1,MARKX=0,LIMIT,RCLICK=0,TIME=200,START=1,T=10,GAMETIME=0;
void AlphaBmp(HDC hdc,HBITMAP hBitmap,int x,int y,short limit,HRGN hRgn,COLORREF col)
{
	BLENDFUNCTION blendfunc;
	HDC hMaskDc;
	HBITMAP hOld=NULL;
	BITMAP Bmp;
	blendfunc.BlendFlags=0;
	blendfunc.AlphaFormat=0;
	blendfunc.SourceConstantAlpha=(unsigned char)limit; 
	blendfunc.BlendOp=AC_SRC_OVER;
	GetObject(hBitmap,sizeof(BITMAP),(LPSTR)&Bmp);
	hMaskDc=CreateCompatibleDC(hdc);
	hOld=(HBITMAP)SelectObject(hMaskDc,hBitmap);
	HDC hTempDC=CreateCompatibleDC(hdc);
	HBITMAP hBitmap2=CreateCompatibleBitmap(hdc,Bmp.bmWidth,Bmp.bmHeight);
	hOld=(HBITMAP)SelectObject(hTempDC,hBitmap2);
	BitBlt(hTempDC,0,0,Bmp.bmWidth,Bmp.bmHeight,hdc,x,y,SRCCOPY);
	AlphaBlend          (hTempDC,0,0,Bmp.bmWidth,Bmp.bmHeight,hMaskDc,0,0,Bmp.bmWidth,Bmp.bmHeight,blendfunc);
	HRGN hR=CreateRectRgn(0,0,Bmp.bmWidth,Bmp.bmHeight);
	HBRUSH hbr=CreateSolidBrush(col);
	CombineRgn(hR,hR,hRgn,RGN_DIFF);
	FillRgn(hTempDC,hR,hbr);	
	TransparentBlt(hdc,x,y,Bmp.bmWidth,Bmp.bmHeight,hTempDC,0,0,Bmp.bmWidth,Bmp.bmHeight,col);
	SelectObject(hTempDC,hOld);
	DeleteObject(hBitmap2);
	DeleteObject(hR);
	DeleteObject(hbr);
	DeleteDC(hTempDC);
	SelectObject(hMaskDc,hOld);
	DeleteDC(hMaskDc);
}
HRGN BitmapToRgn(HBITMAP hBitmap,COLORREF col)
{
	HDC hMemDc;
	HBITMAP hOld;
	COLORREF CPixel;
	HRGN rTemp,hGoal;
	BITMAP Bmp;
    GetObject(hBitmap,sizeof(BITMAP),&Bmp);
	hMemDc=CreateCompatibleDC(NULL);
	hOld=(HBITMAP)SelectObject(hMemDc,hBitmap);
	hGoal=CreateRectRgn(0,0,Bmp.bmWidth,Bmp.bmHeight);
	for(int x=0;x<=Bmp.bmWidth;x++)
		for(int y=0;y<=Bmp.bmHeight;y++)
		{
			CPixel=GetPixel(hMemDc,x,y);
			if(CPixel==col)
			{
                rTemp=CreateRectRgn(x,y,x+1,y+1);
				CombineRgn(hGoal,hGoal,rTemp,RGN_XOR);
				DeleteObject(rTemp);
			}
		}
		SelectObject(hMemDc,hOld);
		DeleteDC(hMemDc);
		return hGoal;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance (hInstance, nCmdShow)) 
		return FALSE;
	//消息循环
	GetMessage(&msg,NULL,NULL,NULL);  //初始化msg
    while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
		else
		{
			tNow = GetTickCount();
			if(tNow-tPre >= T)
				MyPaint(hdc);
		}
    }
	return msg.wParam;
}

//****设计一个窗口类，类似填空题，使用窗口结构体*************************   
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "canvas";
	wcex.hIconSm		= NULL;
	
	return RegisterClassEx(&wcex);
}

// 加载位图并设定各对象的初始值
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	int i,j,ii,jj;
	char filename[20] = "";
	hInst = hInstance;
	HBITMAP bmp;
	hWnd = CreateWindow("canvas", "植物大战僵尸1.0" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}
	
	MoveWindow(hWnd,300,100,1008,630,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	hdc = GetDC(hWnd);
	mdc= CreateCompatibleDC(hdc);
	bufdc= CreateCompatibleDC(hdc);
	bmp = CreateCompatibleBitmap(hdc,1000,600);
	
	SelectObject(mdc,bmp);
	
	b[1][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1));//1wallnut
	b[1][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP2));
	b[1][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
	b[1][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP4));
	b[1][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP5));
	b[1][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP6));
	b[1][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP7));
	b[1][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP8));
	b[1][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP9));
	b[1][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP10));
	b[1][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP11));
	b[1][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP12));
	b[1][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP13));
	b[1][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP14));
	b[1][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP15));
	b[1][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP16));
	b[2][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP17));//2fire
	b[3][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP18));//2wallnut
	b[3][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP19));
	b[3][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP20));
	b[3][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP21));
	b[3][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP22));
	b[3][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP23));
	b[3][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP24));
	b[3][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP25));
	b[3][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP26));
	b[3][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP27));
	b[3][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP28));
	b[4][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP29));//2lajiao
	b[4][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP30));
	b[4][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP31));
	b[4][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP32));
	b[4][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP33));
	b[4][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP34));
	b[4][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP35));
	b[4][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP36));
	b[5][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP37));//2potato
	b[6][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP38));//3wallnut
	b[6][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP39));
	b[6][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP40));
	b[6][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP41));
	b[6][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP42));
	b[6][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP43));
	b[6][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP44));
	b[6][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP45));
	b[6][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP46));
	b[6][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP47));
	b[6][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP48));
	b[6][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP49));
	b[6][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP50));
	b[6][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP51));
	b[6][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP52));
	b[7][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP53));//3potato
	b[8][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP54));//4potato
	b[9][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP55));//background
	b[10][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP56));//dici
	b[10][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP57));
	b[10][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP58));
	b[10][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP59));
	b[10][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP60));
	b[10][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP61));
	b[10][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP62));
	b[10][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP63));
	b[10][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP64));
	b[10][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP65));
	b[10][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP66));
	b[10][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP67));
	b[10][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP68));
	b[10][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP69));
	b[10][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP70));
	b[10][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP71));
	b[10][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP72));
	b[10][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP73));
	b[10][18]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP74));
	b[11][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP75));//fire
	b[11][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP76));
	b[11][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP77));
	b[11][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP78));
	b[11][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP79));
	b[11][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP80));
	b[11][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP81));
    b[11][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP82));
	b[12][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP83));//lajiao
	b[12][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP84));
	b[12][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP85));
	b[12][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP86));
	b[12][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP87));
	b[12][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP88));
	b[12][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP89));
	b[12][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP90));
	b[13][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP91));//peashooter
	b[13][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP92));
	b[13][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP93));
	b[13][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP94));
	b[13][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP95));
	b[13][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP96));
	b[13][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP97));
	b[13][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP98));
	b[13][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP99));
	b[13][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP100));
	b[13][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP101));
	b[13][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP102));
	b[13][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP103));
	b[14][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP104));//potato
	b[14][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP105));
	b[14][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP106));
	b[14][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP107));
	b[14][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP108));
	b[14][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP109));
	b[14][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP110));
	b[14][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP111));
	b[15][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP112));//repeater
	b[15][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP113));
	b[15][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP114));
	b[15][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP115));
	b[15][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP116));
	b[15][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP117));
	b[15][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP118));
	b[15][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP119));
	b[15][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP120));
	b[15][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP121));
	b[15][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP122));
	b[15][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP123));
	b[15][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP124));
	b[15][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP125));
	b[15][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP126));
	b[16][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP127));//snowpea
	b[16][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP128));
	b[16][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP129));
	b[16][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP130));
	b[16][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP131));
	b[16][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP132));
	b[16][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP133));
	b[16][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP134));
	b[16][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP135));
	b[16][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP136));
	b[16][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP137));
	b[16][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP138));
	b[16][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP139));
	b[16][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP140));
	b[16][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP141));
	b[17][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP142));//sunflower
	b[17][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP143));
	b[17][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP144));
	b[17][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP145));
	b[17][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP146));
	b[17][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP147));
	b[17][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP148));
	b[17][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP149));
	b[17][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP150));
	b[17][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP151));
	b[17][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP152));
	b[17][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP153));
	b[17][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP154));
	b[17][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP155));
	b[17][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP156));
	b[17][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP157));
	b[17][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP158));
	b[17][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP159));
	b[18][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP160));//yinying
	b[19][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP161));//chanzi
	b[19][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP162));
	b[20][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP202));//peahit
	b[20][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP203));//baozha
	b[21][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP204));//snowhit
	b[22][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP205));//firehit1
	b[22][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP206));//firehit2
	b[23][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP582));//11wallnut
	b[23][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP583));
	b[23][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP584));
	b[23][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP585));
	b[23][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP586));
	b[23][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP587));
	b[23][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP588));
	b[23][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP589));
	b[23][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP590));
	b[23][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP591));
	b[23][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP592));
	b[23][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP593));
	b[23][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP594));
	b[23][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP595));
	b[24][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP596));//22wallnut
	b[24][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP597));
	b[24][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP598));
	b[24][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP599));
	b[24][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP600));
	b[24][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP601));
	b[24][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP602));
	b[24][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP603));
	b[24][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP604));
	b[24][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP605));
	b[24][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP606));
	b[24][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP607));
	b[24][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP608));
	b[25][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP609));//33wallnut
	b[25][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP610));
	b[25][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP611));
	b[25][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP612));
	b[25][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP613));
	b[25][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP614));
	b[25][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP615));
	b[25][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP616));
	b[25][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP617));
	b[25][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP618));
	b[25][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP619));
	b[25][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP620));
	b[26][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP621));//gangci
	b[26][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP622));
	b[26][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP623));
	b[26][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP624));
	b[26][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP625));
	b[26][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP626));
	b[26][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP627));
	b[26][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP628));
	b[27][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP629));//yintao
	b[27][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP630));
	b[27][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP631));
	b[27][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP632));
	b[27][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP633));
	b[27][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP634));
	b[27][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP635));
	b[28][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP636));//bom
	btb[4][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP163));//tubiao
	btb[4][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP164));
	btb[5][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP165));
	btb[5][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP166));
	btb[10][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP167));
	btb[10][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP168));
	btb[6][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP169));
	btb[6][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP170));
	btb[8][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP171));
	btb[8][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP172));
	btb[9][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP173));
	btb[9][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP174));
	btb[0][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP175));
	btb[0][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP176));
	btb[1][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP637));
	btb[1][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP638));
	btb[12][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP639));
	btb[12][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP640));
	btb[13][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP641));
	btb[13][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP642));	
	b[28][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP179));
	b[29][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP180));
	b[29][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP181));
	b[29][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP182));
	b[29][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP183));
	b[29][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP184));
	b[29][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP185));
	b[29][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP186));
	b[29][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP187));
	b[29][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP188));
	b[29][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP189));
	b[29][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP191));
	b[29][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP192));
	b[29][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP193));
	b[29][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP194));
	b[29][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP195));
	b[29][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP196));
	b[29][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP197));
	b[29][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP198));
	b[29][18]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP199));
	b[29][19]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP200));
	b[29][20]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP201));
	bit[0][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP180));
	bit[0][1]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP181));
	bit[0][2]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP182));
	bit[0][3]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP183));
	bit[0][4]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP184));
	bit[0][5]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP185));
	bit[0][6]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP186));
	bit[0][7]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP187));
	bit[0][8]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP188));
	bit[0][9]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP189));
	bit[0][10]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP190));
	bit[0][11]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP191));
	bit[0][12]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP192));
	bit[0][13]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP193));
	bit[0][14]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP194));
	bit[0][15]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP195));
	bit[0][16]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP196));
	bit[0][17]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP197));
	bit[0][18]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP198));
	bit[0][19]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP199));
	bit[0][20]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP200));
	bit[0][21]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP201));
	bit[1][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP142));//sunflower
	bit[1][1]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP143));
	bit[1][2]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP144));
	bit[1][3]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP145));
	bit[1][4]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP146));
	bit[1][5]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP147));
	bit[1][6]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP148));
	bit[1][7]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP149));
	bit[1][8]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP150));
	bit[1][9]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP151));
	bit[1][10]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP152));
	bit[1][11]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP153));
	bit[1][12]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP154));
	bit[1][13]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP155));
	bit[1][14]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP156));
	bit[1][15]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP157));
	bit[1][16]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP158));
	bit[1][17]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP159));
	bit[2][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP56));//dici
	bit[3][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP582));//wallnut
	bit[4][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP75));//fire
	bit[5][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP83));//lajiao
	bit[6][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP91));//peashooter
	bit[7][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP112));//repeater
	bit[8][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP127));//snowpea
	bit[9][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP621));
	bit[10][0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP629));
	c[1][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP207));//1eat1
	c[1][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP208));
	c[1][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP209));
	c[1][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP210));
	c[1][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP211));
	c[1][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP212));
	c[1][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP213));
	c[1][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP214));
	c[1][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP215));
	c[1][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP216));
	c[1][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP217));
	c[1][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP218));
	c[1][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP219));
	c[1][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP220));
	c[1][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP221));
	c[1][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP222));
	c[1][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP223));
	c[1][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP224));
	c[1][18]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP225));
	c[1][19]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP226));
	c[1][20]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP227));
	c[2][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP228));//1die
	c[2][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP229));
	c[2][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP230));
	c[2][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP231));
	c[2][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP232));
	c[2][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP233));
	c[2][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP234));
	c[2][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP235));
	c[2][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP236));
	c[2][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP237));
	c[3][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP238));//1head
	c[3][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP239));
	c[3][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP240));
	c[3][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP241));
	c[3][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP242));
	c[3][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP243));
	c[3][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP244));
	c[3][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP245));
	c[3][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP246));
	c[3][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP247));
	c[3][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP248));
	c[3][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP249));
	c[4][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP250));//1slowwalk
	c[4][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP251));
	c[4][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP252));
	c[4][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP253));
	c[4][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP254));
	c[4][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP255));
	c[4][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP256));
	c[4][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP257));
	c[4][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP258));
	c[4][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP259));
	c[4][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP260));
	c[4][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP261));
	c[4][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP262));
	c[4][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP263));
	c[4][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP264));
	c[4][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP265));
	c[4][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP266));
	c[4][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP267));
	c[4][18]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP268));
	c[4][19]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP269));
	c[4][20]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP270));
	c[4][21]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP271));
	c[4][22]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP272));
	c[4][23]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP273));
	c[4][24]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP274));
	c[4][25]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP275));
	c[4][26]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP276));
	c[4][27]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP277));
	c[4][28]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP278));
	c[4][29]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP279));
	c[4][30]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP280));
	c[5][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP281));//1dieeat
	c[5][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP282));
	c[5][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP283));
	c[5][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP284));
	c[5][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP285));
	c[5][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP286));
	c[5][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP287));
	c[5][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP288));
	c[5][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP289));
	c[5][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP290));
	c[5][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP291));
	c[6][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP292));//1diewalk
	c[6][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP293));
	c[6][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP294));
	c[6][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP295));
	c[6][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP296));
	c[6][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP297));
	c[6][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP298));
	c[6][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP299));
	c[6][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP300));
	c[6][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP301));
	c[6][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP302));
	c[6][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP303));
	c[6][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP304));
	c[6][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP305));
	c[6][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP306));
	c[6][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP307));
	c[6][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP308));
	c[6][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP309));
	c[7][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP310));//burn1
	c[7][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP311));
	c[7][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP312));
	c[7][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP313));
	c[7][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP314));
	c[7][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP315));
	c[7][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP316));
	c[7][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP317));
	c[7][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP318));
	c[7][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP319));
	c[7][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP320));
	c[7][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP321));
	c[7][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP322));
	c[7][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP323));
	c[7][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP324));
	c[7][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP325));
	c[7][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP326));
	c[7][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP327));
	c[7][18]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP328));
	c[7][19]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP329));
	c[8][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP330));//1stand1
	c[8][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP331));
	c[8][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP332));
	c[8][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP333));
	c[8][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP334));
	c[8][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP335));
	c[8][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP336));
	c[8][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP337));
	c[8][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP338));
	c[8][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP339));
	c[8][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP340));
	c[8][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP341));
	c[8][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP342));
	c[8][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP343));
	c[8][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP344));
	c[8][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP345));
	c[8][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP346));
	c[8][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP347));
	c[8][18]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP348));
	c[8][19]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP349));
	c[8][20]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP350));
	c[8][21]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP351));
	c[9][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP352));//1stand1
	c[9][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP353));
	c[9][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP354));
	c[9][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP355));
	c[9][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP356));
	c[9][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP357));
	c[9][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP358));
	c[9][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP359));
	c[9][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP360));
	c[9][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP361));
	c[9][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP362));
	c[9][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP363));
	c[9][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP364));
	c[9][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP365));
	c[9][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP366));
	c[9][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP367));
	c[9][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP368));
	c[9][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP369));
	c[9][18]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP370));
	c[9][19]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP371));
	c[9][20]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP372));
	c[9][21]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP373));
	a[0][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP374));//1dava
	a[0][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP375));
	a[0][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP376));
	a[0][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP377));
	a[0][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP378));
	a[0][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP379));
	a[0][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP380));
    a[0][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP381));
	a[0][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP382));
	a[0][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP383));
	a[0][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP384));
	a[0][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP385));
	a[0][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP386));
	a[0][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP387));
	a[0][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP388));
	a[0][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP389));
	a[0][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP390));
	a[1][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP391));
	a[1][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP392));//2dava
	a[1][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP393));
	a[1][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP394));
	a[1][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP395));
	a[1][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP396));
	a[2][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP397));//3dava
	a[2][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP398));
	a[2][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP399));
	a[2][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP400));
	a[2][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP401));
	a[2][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP402));
	a[2][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP403));
	a[2][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP404));
	a[2][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP405));
	a[2][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP406));
	a[2][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP407));
	a[2][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP408));
	a[2][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP409));
	a[3][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP410));//start
	a[4][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP411));//end
	a[5][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP412));//help
	a[6][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP413));//talk
	a[7][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP414));//continue
	a[3][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP415));//win
	a[3][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP416));//stone
	a[3][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP417));//line
	a[3][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP418));//hand
	a[3][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP419));//advantrue1
	a[3][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP420));//advantrue2
	a[3][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP421));//button
	a[3][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP422));//flag
	a[3][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP423));//progress1
	a[3][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP424));//progress2
	a[8][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP425));//word
	a[8][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP426));
	a[8][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP427));
	a[9][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP428));//2sunflower
	a[9][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP429));
	a[9][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP430));
	a[9][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP431));
	a[9][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP432));
	a[9][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP433));
	a[9][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP434));
	a[9][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP435));
	a[9][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP436));
	a[9][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP437));
	a[9][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP438));
	a[9][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP439));
	a[9][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP440));
	a[9][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP441));
	a[9][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP442));
	a[9][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP443));
	a[9][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP444));
	a[9][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP445));
	a[3][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP446));//word
	a[3][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP447));
	a[3][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP448));//zomhead
	a[3][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP449));//zuihou
	a[3][15]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP450));//yidabo
	a[3][16]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP451));//menu
	a[3][17]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP452));//button2
	c[10][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP453));//photo
	c[10][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP454));
	c[10][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP455));
	c[10][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP456));
	d[1][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP484));//flageat
	d[1][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP485));
	d[1][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP486));
	d[1][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP487));
	d[1][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP488));
	d[1][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP489));
	d[1][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP490));
	d[1][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP491));
	d[1][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP492));
	d[1][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP493));
	d[1][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP494));
	d[4][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP472));//flagwalk
	d[4][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP473));
	d[4][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP474));
	d[4][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP475));
	d[4][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP476));
	d[4][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP477));
	d[4][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP478));
	d[4][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP479));
	d[4][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP480));
	d[4][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP481));
	d[4][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP482));
	d[4][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP483));
	d[5][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP507));//flagdieeat
	d[5][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP508));
	d[5][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP509));
	d[5][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP510));
	d[5][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP511));
	d[5][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP512));
	d[5][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP513));
	d[5][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP514));
	d[5][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP515));
	d[5][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP516));
	d[5][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP517));
	d[6][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP495));//flagdiewalk
	d[6][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP496));
	d[6][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP497));
	d[6][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP498));
	d[6][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP499));
	d[6][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP500));
	d[6][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP501));
	d[6][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP502));
	d[6][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP503));
	d[6][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP504));
	d[6][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP505));
	d[6][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP506));
	d[8][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP457));//flagstand
	d[8][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP458));
	d[8][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP459));
	d[8][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP460));
	d[8][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP461));
	d[8][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP462));
	d[8][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP463));
	d[8][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP464));
	d[8][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP465));
	d[8][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP466));
	d[8][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP467));
	d[8][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP468));
	d[8][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP469));
	d[8][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP470));
	d[8][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP471));
	e[2][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP518));//balldie
	e[2][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP519));
	e[2][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP520));
	e[2][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP521));
	e[2][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP522));
	e[2][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP523));
	e[2][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP524));
	e[6][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP525));//balldiewalk
	e[6][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP526));
	e[6][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP527));
	e[6][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP528));
	e[6][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP529));
	e[6][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP530));
	e[6][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP531));
	e[6][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP532));
	e[6][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP533));
	e[6][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP534));
	e[5][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP535));//balldieeat
	e[5][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP536));
	e[5][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP537));
	e[5][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP538));
	e[5][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP539));
	e[5][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP540));
	e[5][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP541));
	e[5][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP542));
	e[5][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP543));
	e[5][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP544));
	e[1][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP545));//balleat
	e[1][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP546));
	e[1][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP547));
	e[1][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP548));
	e[1][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP549));
	e[1][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP550));
	e[1][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP551));
	e[1][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP552));
	e[1][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP553));
	e[1][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP554));
	e[1][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP555));
	e[4][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP556));//ballwalk
	e[4][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP557));
	e[4][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP558));
	e[4][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP559));
	e[4][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP560));
	e[4][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP561));
	e[4][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP562));
	e[4][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP563));
	e[4][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP564));
	e[4][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP565));
	e[4][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP566));
	e[8][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP567));//ballstand
	e[8][1]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP568));
	e[8][2]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP569));
	e[8][3]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP570));
	e[8][4]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP571));
	e[8][5]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP572));
	e[8][6]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP573));
	e[8][7]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP574));
	e[8][8]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP575));
	e[8][9]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP576));
	e[8][10]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP577));
	e[8][11]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP578));
	e[8][12]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP579));
	e[8][13]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP580));
	e[8][14]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP581));
	e[9][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP643));//shadow
	e[10][0]=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP644));//shadow2
	for(i=0;i<16;i++)
		GetObject(b[1][i],sizeof(BITMAP),&bm[1][i]);
	for(i=0;i<1;i++)
		GetObject(b[2][i],sizeof(BITMAP),&bm[2][i]);
	for(i=0;i<11;i++)
		GetObject(b[3][i],sizeof(BITMAP),&bm[3][i]);
	for(i=0;i<8;i++)
		GetObject(b[4][i],sizeof(BITMAP),&bm[4][i]);
	for(i=0;i<1;i++)
		GetObject(b[5][i],sizeof(BITMAP),&bm[5][i]);
	for(i=0;i<15;i++)
		GetObject(b[6][i],sizeof(BITMAP),&bm[6][i]);
	for(i=0;i<1;i++)
		GetObject(b[7][i],sizeof(BITMAP),&bm[7][i]);
	for(i=0;i<1;i++)
		GetObject(b[8][i],sizeof(BITMAP),&bm[8][i]);
	for(i=0;i<1;i++)
		GetObject(b[9][i],sizeof(BITMAP),&bm[9][i]);
	for(i=0;i<19;i++)
		GetObject(b[10][i],sizeof(BITMAP),&bm[10][i]);
	for(i=0;i<8;i++)
		GetObject(b[11][i],sizeof(BITMAP),&bm[11][i]);
	for(i=0;i<8;i++)
		GetObject(b[12][i],sizeof(BITMAP),&bm[12][i]);
	for(i=0;i<13;i++)
		GetObject(b[13][i],sizeof(BITMAP),&bm[13][i]);
	for(i=0;i<8;i++)
		GetObject(b[14][i],sizeof(BITMAP),&bm[14][i]);
	for(i=0;i<15;i++)
		GetObject(b[15][i],sizeof(BITMAP),&bm[15][i]);
	for(i=0;i<15;i++)
		GetObject(b[16][i],sizeof(BITMAP),&bm[16][i]);
	for(i=0;i<18;i++)
		GetObject(b[17][i],sizeof(BITMAP),&bm[17][i]);
	for(i=0;i<1;i++)
		GetObject(b[18][i],sizeof(BITMAP),&bm[18][i]);
	for(i=0;i<2;i++)
		GetObject(b[19][i],sizeof(BITMAP),&bm[19][i]);
	for(i=0;i<2;i++)
		GetObject(b[19][i],sizeof(BITMAP),&bm[19][i]);
	for(i=0;i<2;i++)
		GetObject(b[20][i],sizeof(BITMAP),&bm[20][i]);
	for(i=0;i<2;i++)
		GetObject(b[22][i],sizeof(BITMAP),&bm[22][i]);
	GetObject(b[21][0],sizeof(BITMAP),&bm[21][0]);
	for(i=0;i<2;i++)
		GetObject(btb[0][i],sizeof(BITMAP),&bmtb[0][i]);
	for(i=0;i<2;i++)
		GetObject(btb[1][i],sizeof(BITMAP),&bmtb[1][i]);
	for(i=0;i<2;i++)
		GetObject(btb[4][i],sizeof(BITMAP),&bmtb[4][i]);
	for(i=0;i<2;i++)
		GetObject(btb[5][i],sizeof(BITMAP),&bmtb[5][i]);
	for(i=0;i<2;i++)
		GetObject(btb[6][i],sizeof(BITMAP),&bmtb[6][i]);
	for(i=0;i<2;i++)
		GetObject(btb[8][i],sizeof(BITMAP),&bmtb[8][i]);
	for(i=0;i<2;i++)
		GetObject(btb[9][i],sizeof(BITMAP),&bmtb[9][i]);
	for(i=0;i<2;i++)
		GetObject(btb[10][i],sizeof(BITMAP),&bmtb[10][i]);
	for(i=0;i<2;i++)
		GetObject(btb[12][i],sizeof(BITMAP),&bmtb[12][i]);
	for(i=0;i<2;i++)
		GetObject(btb[13][i],sizeof(BITMAP),&bmtb[13][i]);
	GetObject(b[28][0],sizeof(BITMAP),&bm[28][0]);
	for(i=0;i<21;i++)
		GetObject(b[29][i],sizeof(BITMAP),&bm[29][i]);
	for(i=0;i<21;i++)
		GetObject(c[1][i],sizeof(BITMAP),&cm[1][i]);
	for(i=0;i<10;i++)
		GetObject(c[2][i],sizeof(BITMAP),&cm[2][i]);
	for(i=0;i<12;i++)
		GetObject(c[3][i],sizeof(BITMAP),&cm[3][i]);
	for(i=0;i<31;i++)
		GetObject(c[4][i],sizeof(BITMAP),&cm[4][i]);
	for(i=0;i<11;i++)
		GetObject(c[5][i],sizeof(BITMAP),&cm[5][i]);
	for(i=0;i<18;i++)
		GetObject(c[6][i],sizeof(BITMAP),&cm[6][i]);
	for(i=0;i<20;i++)
		GetObject(c[7][i],sizeof(BITMAP),&cm[7][i]);
	for(i=0;i<22;i++)
		GetObject(c[8][i],sizeof(BITMAP),&cm[8][i]);
	for(i=0;i<22;i++)
		GetObject(c[9][i],sizeof(BITMAP),&cm[9][i]);
	for(i=0;i<17;i++)
		GetObject(a[0][i],sizeof(BITMAP),&am[0][i]);
	for(i=0;i<6;i++)
		GetObject(a[1][i],sizeof(BITMAP),&am[1][i]);
	for(i=0;i<13;i++)
		GetObject(a[2][i],sizeof(BITMAP),&am[2][i]);
	GetObject(a[3][0],sizeof(BITMAP),&am[3][0]);
	GetObject(a[4][0],sizeof(BITMAP),&am[4][0]);
	GetObject(a[5][0],sizeof(BITMAP),&am[5][0]);
	GetObject(a[6][0],sizeof(BITMAP),&am[6][0]);
	GetObject(a[7][0],sizeof(BITMAP),&am[7][0]);//cd,8000,8000,10000,10000,15000,30000,15000,40000
	tubiao[0].plant=0,tubiao[0].cd=8000,tubiao[0].x=0,tubiao[0].y=0,tubiao[0].bright=1,tubiao[0].isclick=false,tubiao[0].price=50,tubiao[0].time=0;
	tubiao[1].plant=6,tubiao[1].cd=8000,tubiao[1].x=100,tubiao[1].y=0,tubiao[1].bright=1,tubiao[1].isclick=false,tubiao[1].price=100,tubiao[1].time=0;
	tubiao[2].plant=8,tubiao[2].cd=10000,tubiao[2].x=200,tubiao[2].y=0,tubiao[2].bright=1,tubiao[2].isclick=false,tubiao[2].price=200,tubiao[2].time=0;
	tubiao[3].plant=9,tubiao[3].cd=10000,tubiao[3].x=300,tubiao[3].y=0,tubiao[3].bright=1,tubiao[3].isclick=false,tubiao[3].price=175,tubiao[3].time=0;
	tubiao[4].plant=5,tubiao[4].cd=15000,tubiao[4].x=400,tubiao[4].y=0,tubiao[4].bright=1,tubiao[4].isclick=false,tubiao[4].price=175,tubiao[4].time=0;
	tubiao[5].plant=1,tubiao[5].cd=30000,tubiao[5].x=500,tubiao[5].y=0,tubiao[5].bright=1,tubiao[5].isclick=false,tubiao[5].price=125,tubiao[5].time=0;
	tubiao[6].plant=4,tubiao[6].cd=15000,tubiao[6].x=600,tubiao[6].y=0,tubiao[6].bright=1,tubiao[6].isclick=false,tubiao[6].price=100,tubiao[6].time=0;
	tubiao[7].plant=10,tubiao[7].cd=40000,tubiao[7].x=700,tubiao[7].y=0,tubiao[7].bright=1,tubiao[7].isclick=false,tubiao[7].price=125,tubiao[7].time=0;
	tubiao[8].plant=12,tubiao[8].cd=15000,tubiao[8].x=800,tubiao[8].y=0,tubiao[8].bright=1,tubiao[8].isclick=false,tubiao[8].price=100,tubiao[8].time=0;
	tubiao[9].plant=13,tubiao[9].cd=40000,tubiao[9].x=900,tubiao[9].y=0,tubiao[9].bright=1,tubiao[9].isclick=false,tubiao[9].price=175,tubiao[9].time=0;
	czback.x=12,czback.y=100;
	cz.x=20,cz.y=110,cz.inback=true;
	for(i=1,ii=70;i<=5;i++,ii+=100)
		for(j=1,jj=150;j<=9;j++,jj+=82){
			map[i][j].x=jj,map[i][j].y=ii,map[i][j].i=-1,map[i][j].j=0,map[i][j].marks=0,
				map[i][j].sunj=0,map[i][j].have=0,map[i][j].limit=255,map[i][j].PAINT=1,map[i][j].life=1;
		}
		for(i=0;i<30;i++){
			plant[i].x=0;
			if(i==2||i==3||i==1){
				plant[i].y=0;
			}
			else if(i==4||i==12){
				plant[i].y=70;
				plant[i].x=-5;
			}
			else if(i==5)
				plant[i].y=10;
			else if(i==7)
				plant[i].y=50;
			else if(i==10)
				plant[i].y=10;
			else if(i==13){
				plant[i].y=10;
				plant[i].x=-30;
			}
			else
				plant[i].y=20;
		}
		hrgn[1][0]=BitmapToRgn(bit[1][0],RGB(0,0,0));
		hrgn[3][0]=BitmapToRgn(bit[3][0],RGB(0,0,0));
		hrgn[2][0]=BitmapToRgn(bit[2][0],RGB(0,0,0));
		hrgn[4][0]=BitmapToRgn(bit[4][0],RGB(0,0,0));
		hrgn[6][0]=BitmapToRgn(bit[6][0],RGB(0,0,0));
		hrgn[7][0]=BitmapToRgn(bit[7][0],RGB(0,0,0));
		hrgn[8][0]=BitmapToRgn(bit[8][0],RGB(0,0,0));
		hrgn[5][0]=BitmapToRgn(bit[5][0],RGB(0,0,0));
		hrgn[9][0]=BitmapToRgn(bit[9][0],RGB(0,0,0));/////gangci
		hrgn[10][0]=BitmapToRgn(bit[10][0],RGB(0,0,0));/////yintao
		hrgn[0][0]=BitmapToRgn(bit[0][0],RGB(0,0,0));
		hrgn[0][1]=BitmapToRgn(bit[0][1],RGB(0,0,0));
		hrgn[0][2]=BitmapToRgn(bit[0][2],RGB(0,0,0));
		hrgn[0][3]=BitmapToRgn(bit[0][3],RGB(0,0,0));
		hrgn[0][4]=BitmapToRgn(bit[0][4],RGB(0,0,0));
		hrgn[0][5]=BitmapToRgn(bit[0][5],RGB(0,0,0));
		hrgn[0][6]=BitmapToRgn(bit[0][6],RGB(0,0,0));
		hrgn[0][7]=BitmapToRgn(bit[0][7],RGB(0,0,0));
		hrgn[0][8]=BitmapToRgn(bit[0][8],RGB(0,0,0));
		hrgn[0][9]=BitmapToRgn(bit[0][9],RGB(0,0,0));
		hrgn[0][10]=BitmapToRgn(bit[0][10],RGB(0,0,0));
		hrgn[0][11]=BitmapToRgn(bit[0][11],RGB(0,0,0));
		hrgn[0][12]=BitmapToRgn(bit[0][12],RGB(0,0,0));
		hrgn[0][13]=BitmapToRgn(bit[0][13],RGB(0,0,0));
		hrgn[0][14]=BitmapToRgn(bit[0][14],RGB(0,0,0));
		hrgn[0][15]=BitmapToRgn(bit[0][15],RGB(0,0,0));
		hrgn[0][16]=BitmapToRgn(bit[0][16],RGB(0,0,0));
		hrgn[0][17]=BitmapToRgn(bit[0][17],RGB(0,0,0));
		hrgn[0][18]=BitmapToRgn(bit[0][18],RGB(0,0,0));
		hrgn[0][19]=BitmapToRgn(bit[0][19],RGB(0,0,0));
		hrgn[0][20]=BitmapToRgn(bit[0][20],RGB(0,0,0));
		hrgn[11][0]=BitmapToRgn(e[9][0],RGB(255,255,255));
		hrgn[12][0]=BitmapToRgn(e[10][0],RGB(255,255,255));
		dava.x=0,dava.y=80,dava.j=0,dava.flag=0;
		hand.x=220,hand.y=250,hand.j=0,z=0;
		background.x=0;
		background.y=0;
		background.v=1;
		sunnum.num=5000,sunnum.x=60,sunnum.y=70;
		AF.ANFANG=1,AF.i=-1;
		sun.x=9999,sun.j=0;
		suntime=0;
		zombiet=0;
		memset(pnum,0,sizeof(pnum));
		memset(znum,0,sizeof(znum));
		//mciSendString("open .\\re\\zhongxia.mp3",NULL,0,NULL);
		///////////////////
		
		map[1][1].i=0;map[1][2].i=9;map[1][3].i=9;map[1][4].i=-1;map[1][5].i=5;map[1][6].i=9;map[1][8].i=5;map[1][9].i=1;
		map[2][1].i=0;map[2][2].i=8;map[2][3].i=8;map[2][5].i=1;map[2][6].i=1;map[2][7].i=2;map[2][8].i=3;
		map[3][2].i=4;map[3][3].i=4;map[3][4].i=4;map[3][5].i=4;map[3][6].i=4;map[3][7].i=4;map[3][8].i=4;map[3][9].i=4;
		map[4][1].i=0;map[4][2].i=6;map[4][3].i=6;map[4][4].i=8;map[4][7].i=5;
		map[5][1].i=0;map[5][2].i=6;map[5][3].i=9;map[5][4].i=8;
		for(i=1;i<=5;i++){
			for(j=1;j<=9;j++)
				if(map[i][j].i==0){
					map[i][j].time=0;
					map[i][j].marks=1;
					map[i][j].life=1000;
				}
				else if(map[i][j].i==1)
					map[i][j].life=5000;
				else if(map[i][j].i==2)
					map[i][j].life=3000;
				else if(map[i][j].i==3)
					map[i][j].life=1000;
				else if(map[i][j].i==4)
					map[i][j].life=99999;
				else if(map[i][j].i==5)
					map[i][j].life=1000;
				else if(map[i][j].i==6){//豌豆射手生产
					map[i][j].time=0;
					map[i][j].marks=0;
					map[i][j].life=1000;
					pnum[i]++;
				}
				else if(map[i][j].i==9){//寒冰射手生产
					map[i][j].time=0;
					map[i][j].marks=0;
					map[i][j].life=1000;
					pnum[i]++;
				}
				else if(map[i][j].i==8){//repeater生产
					map[i][j].time=0;
					map[i][j].marks=0;
					map[i][j].repeater=0;
					map[i][j].life=1000;
					pnum[i]++;
				}
				else if(map[i][j].i==10)
					map[i][j].life=100000;
		}
		MyPaint(hdc);
		return true;
}
void MyPaint(HDC hdc)
{
	if(START<10&&START!=1){
		mciSendString("play .\\re\\sky.wav",NULL,0,NULL);
	}
	int i,j,numplant,k,nnum,len,px,FLAG=1,x,y;
	char st[50];
	//HPEN hf;
	TEXTMETRIC tm;
	HFONT hf_black;
	GetClientRect(hWnd,&rect);
	if(START==1){
		if(CLICK)
			START=2;
		SelectObject(bufdc,a[3][0]);
		BitBlt(mdc,0,0,1000,600,bufdc,0,0,SRCCOPY);
		BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
	}
	else if(START==2){
		T=50;
		SelectObject(bufdc,a[3][2]);
		BitBlt(mdc,0,0,1000,600,bufdc,0,0,SRCCOPY);
		if(hand.j<=5){
			GetObject(a[3][4],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[3][4]);
			TransparentBlt(mdc,hand.x,hand.y,bp.bmWidth/7,bp.bmHeight,bufdc,bp.bmWidth*hand.j/7,0,bp.bmWidth/7,bp.bmHeight,RGB(255,255,255));
			hand.j++;
		}
		else
		{
			GetObject(a[3][4],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[3][4]);
			TransparentBlt(mdc,hand.x,hand.y,bp.bmWidth/7,bp.bmHeight,bufdc,bp.bmWidth*hand.j/7,0,bp.bmWidth/7,bp.bmHeight,RGB(255,255,255));
		}
		if(movex>=530&&movex<=530+331&&movey>=130&&movey<=130+147){
			GetObject(a[3][6],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[3][6]);
			TransparentBlt(mdc,530,130,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
			if(CLICK){
				START=4;
				//T=10;
				//mciSendString("play .\\re\\sky.wav",NULL,0,NULL);
				//PlaySound("c:\\porridge\\sky.wav",NULL,SND_SYNC|SND_LOOP|SND_ASYNC);
			}
		}
		else{
			GetObject(a[3][5],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[3][5]);
			TransparentBlt(mdc,530,130,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
		}
		if(CLICK){
			if(movex>=802&&movex<=877&&movey>=521&&movey<=554)
				START=3;
			else if(movex>=894&&movex<=967&&movey>=513&&movey<=544)
				PostQuitMessage(0);		
		}
		BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
	}
	else if(START==3){
		SelectObject(bufdc,b[3][2]);
		BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
		GetObject(a[5][0],sizeof(BITMAP),&bp);
		SelectObject(bufdc,a[5][0]);
		TransparentBlt(mdc,200,100,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,255,0));
		BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
		if(CLICK)
			START=2;
	}
	else if(START==4){
		//mciSendString("play .\\re\\sky.wav",NULL,0,NULL);
		SelectObject(bufdc,b[9][0]);
		BitBlt(mdc,0,0,1000,600,bufdc,0,0,SRCCOPY);
		if(dava.flag==0){
			GetObject(a[dava.flag][dava.j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[dava.flag][dava.j]);
			TransparentBlt(mdc,dava.x,dava.y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			dava.j=(dava.j+1)%17;
			if(CLICK){
				dava.flag=1;
				dava.j=0;
				mciSendString("play .\\re\\dave.wav",NULL,0,NULL);
				//PlaySound("c:\\porridge\\dave.wav",NULL,SND_SYNC|SND_ASYNC);
			}
		}
		else if(dava.flag==1){
			if(dava.j==12){
				dava.flag=2;
				dava.j=0;
			}
			GetObject(a[2][dava.j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[2][dava.j]);
			TransparentBlt(mdc,dava.x,dava.y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			dava.j=(dava.j+1)%13;
			GetObject(a[6][0],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[6][0]);
			TransparentBlt(mdc,dava.x+230,dava.y+50,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,255,0));
			GetObject(a[3][11],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[3][11]);
			TransparentBlt(mdc,dava.x+300,dava.y+90,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,0,0));
		}
		else if(dava.flag==2){
			GetObject(a[0][dava.j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[0][dava.j]);
			TransparentBlt(mdc,dava.x,dava.y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			dava.j=(dava.j+1)%17;
			GetObject(a[6][0],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[6][0]);
			TransparentBlt(mdc,dava.x+230,dava.y+50,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,255,0));
			GetObject(a[3][11],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[3][11]);
			TransparentBlt(mdc,dava.x+300,dava.y+90,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,0,0));
			if(CLICK){
				dava.flag=3;
				dava.j=0;
			}
		}
		else if(dava.flag==3){
			if(dava.j==5)
				START=5;
			GetObject(a[1][dava.j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,a[1][dava.j]);
			TransparentBlt(mdc,dava.x,dava.y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			dava.j=(dava.j+1)%6;
		}
		BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
	}
	else if(START==5){
		T=10;
		SelectObject(bufdc,b[9][0]);
		BitBlt(mdc,0,0,1000,600,bufdc,background.x,0,SRCCOPY);
		if(background.x>100+stepi&&background.x<300){
			zombie.flag=(zbj%3)+1;
			zombie.x=1000-72,zombie.y=zombiey2[zbj],zombie.j=0,zombie.i=9,zombie.life=0;
			Zombie.push_back(zombie);
			zbj=(zbj+1)%20;
			stepi=stepi+10;
		}
		for(it1=Zombie.begin();it1!=Zombie.end();){
			if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+80,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+90,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+40,(*it1).y+137,50,hrgn[11][0],RGB(255,255,255));
			it1++;
		}
		sort(Zombie.begin(),Zombie.end(),cmp);
		for(it1=Zombie.begin();it1!=Zombie.end();){
			if(background.x<400)
				(*it1).x-=background.v;
			if((*it1).flag==1){
			GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,c[(*it1).i][(*it1).j]);
			TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			if((*it1).life==0)
				(*it1).j=((*it1).j+1)%22;
			}
			else if((*it1).flag==2){
			GetObject(d[8][(*it1).j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,d[8][(*it1).j]);
			TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			if((*it1).life==0)
				(*it1).j=((*it1).j+1)%15;
			}
			else if((*it1).flag==3){
			GetObject(e[8][(*it1).j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,e[8][(*it1).j]);
			TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			if((*it1).life==0)
				(*it1).j=((*it1).j+1)%15;
			}
			(*it1).life=((*it1).life+1)%5;
			it1++;
		}	
		if(background.x<400)
			background.x+=background.v;
		else if(CLICK)
			START=6;
		BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
	}
	else if(START==6){
		SelectObject(bufdc,b[9][0]);
		BitBlt(mdc,0,0,1000,600,bufdc,background.x,0,SRCCOPY);
		for(it1=Zombie.begin();it1!=Zombie.end();){
			if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+80,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+90,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+40,(*it1).y+137,50,hrgn[11][0],RGB(255,255,255));
			it1++;
		}
		for(it1=Zombie.begin();it1!=Zombie.end();){
			(*it1).x+=background.v;
			if((*it1).flag==1){
			GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,c[(*it1).i][(*it1).j]);
			TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			if((*it1).life==0)
				(*it1).j=((*it1).j+1)%22;
			}
			else if((*it1).flag==2){
			GetObject(d[8][(*it1).j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,d[8][(*it1).j]);
			TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			if((*it1).life==0)
				(*it1).j=((*it1).j+1)%15;
			}
			else if((*it1).flag==3){
			GetObject(e[8][(*it1).j],sizeof(BITMAP),&bp);
			SelectObject(bufdc,e[8][(*it1).j]);
			TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
			if((*it1).life==0)
				(*it1).j=((*it1).j+1)%15;
			}
			(*it1).life=((*it1).life+1)%5;
			it1++;
		}	
		if(background.x>100)
			background.x-=background.v;
		else {
			START=7;
			while(!Zombie.empty()){
				it1=Zombie.begin();
				Zombie.erase(it1);
			}
		}
		BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
	}
	else if(START==7||START==8||START==9){
		T=1000;
		SelectObject(bufdc,b[9][0]);
		BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
		GetObject(a[8][START-7],sizeof(BITMAP),&bp);
		SelectObject(bufdc,a[8][START-7]);
		TransparentBlt(mdc,350,200,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
		BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
		START++;
		if(START==10){
			//T=40;********
			T=50;
			mciSendString("stop .\\re\\sky.wav",NULL,0,NULL);
		    GAMETIME=3300;
		}
	}
	else if(START==10){
		mciSendString("play .\\re\\gnite.wav",NULL,0,NULL);
		GAMETIME++;
		SelectObject(bufdc,b[9][0]);
		BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
		sort(Zombie.begin(),Zombie.end(),cmp);
		sort(vec.begin(),vec.end());
		if(RCLICK){//右键取消
			cz.inback=true;
			tubiao[which].isclick=0;
			MARKX=0;
			AF.ANFANG=0;
		}
		for(i=1;i<=5;i++){
			if(pnum[i]&&znum[i])
				for(j=1;j<=9;j++)
					if(map[i][j].marks==0&&(map[i][j].i==6||map[i][j].i==8||map[i][j].i==9)&&map[i][j].life>0){
						map[i][j].time=0;
						map[i][j].marks=1;
					}
					if(znum[i]==0&&pnum[i]!=0)
						for(j=1;j<=9;j++)
							if((map[i][j].i==6||map[i][j].i==8||map[i][j].i==9)&&map[i][j].life>0)
								map[i][j].marks=0;
		}
		/***********************/
		for(it1=Zombie.begin();it1!=Zombie.end();){//画僵尸阴影
					if((*it1).stata==2){//burn
						if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+100,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+65,(*it1).y+127,50,hrgn[11][0],RGB(255,255,255));
						//it1++;
					}
					
					else if((*it1).stata==4){//diewalk
						if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+100,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+65,(*it1).y+127,50,hrgn[11][0],RGB(255,255,255));
						//it1++;
					}
					else if((*it1).stata==6){//eat
						if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+80,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+50,(*it1).y+137,50,hrgn[11][0],RGB(255,255,255));
						//it1++;
					}
					else if((*it1).stata==7){//nohead eat
						if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+80,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+25,(*it1).y+137,50,hrgn[11][0],RGB(255,255,255));
						//it1++;
					}
					else if((*it1).stata==0){//walk
						if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+100,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+65,(*it1).y+127,50,hrgn[11][0],RGB(255,255,255));
						
					}
					it1++;
			}
		/***********************/
		for(it=vec.begin();it!=vec.end();){//画粒子阴影
				if((*it).x>1000){//粒子出界
					vec.erase(it);
					continue;
				}
				AlphaBmp(mdc,e[10][0],(*it).x,(*it).y+72,80,hrgn[12][0],RGB(255,255,255));
				it++;
		}
		for(i=1;i<=5;i++)//画map上的植物
			for(j=1;j<=9;j++){
				if(map[i][j].life<0){//去掉死去的植物
					if(map[i][j].i==6||map[i][j].i==8||map[i][j].i==9)
						pnum[i]--;
					map[i][j].i=-1;
				}
				if(map[i][j].i==0){//向日葵
					AlphaBmp(mdc,e[9][0],map[i][j].x-5,map[i][j].y+72,80,hrgn[11][0],RGB(255,255,255));
					if(map[i][j].marks){
						map[i][j].time++;//生产时间
						if(map[i][j].time>=400){
							map[i][j].time=0;
							//map[i][j].limit=255;
							map[i][j].have=0;
						}
						else if(map[i][j].time>=300){
							map[i][j].have=1;
							map[i][j].PAINT=1;
						}
						else if(map[i][j].time>=260)
							map[i][j].PAINT=0;
						if(map[i][j].PAINT){
							GetObject(b[17][map[i][j].j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,b[17][map[i][j].j]);
							TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
						}
						else{
							GetObject(a[9][map[i][j].j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,a[9][map[i][j].j]);
							TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight/2,bufdc,0,74,bp.bmWidth,bp.bmHeight/2,RGB(255,255,255));
						}
						if(map[i][j].have){
							/*GetObject(b[29][map[i][j].sunj],sizeof(BITMAP),&bp);
							SelectObject(bufdc,b[29][map[i][j].sunj]);
							TransparentBlt(mdc,map[i][j].x-30,map[i][j].y+30,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							map[i][j].sunj=(map[i][j].sunj+1)%21;*/
							LIMIT=175+(400-map[i][j].time)*80/100;
						    AlphaBmp(mdc,bit[0][map[i][j].sunj],map[i][j].x-30,map[i][j].y+30,LIMIT,hrgn[0][map[i][j].sunj],RGB(0,0,0));
						    map[i][j].sunj=(map[i][j].sunj+1)%21;
						}
						
					}
					else{
						GetObject(b[17][map[i][j].j],sizeof(BITMAP),&bp);
						SelectObject(bufdc,b[17][map[i][j].j]);
						TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					}
					map[i][j].j=(map[i][j].j+1)%18;
				}
				else if(map[i][j].i==1){//坚果
					GetObject(b[23][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[23][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%14;
					if(map[i][j].life<8000){
						map[i][j].i=2;
						map[i][j].j=0;
					}
				}
				else if(map[i][j].i==2){
					GetObject(b[24][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[24][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%13;
					if(map[i][j].life<4000){
						map[i][j].i=3;
						map[i][j].j=0;
					}
				}
				else if(map[i][j].i==3){
					GetObject(b[25][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[25][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%12;
				}
				else if(map[i][j].i==4){//地刺
					GetObject(b[10][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[10][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%19;
				}
				else if(map[i][j].i==5){//fire
					AlphaBmp(mdc,e[9][0],map[i][j].x-5,map[i][j].y+72,80,hrgn[11][0],RGB(255,255,255));
					GetObject(b[11][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[11][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%8;
				}
				else if(map[i][j].i==6){//豌豆射手
					AlphaBmp(mdc,e[9][0],map[i][j].x-10,map[i][j].y+67,80,hrgn[11][0],RGB(255,255,255));
					GetObject(b[13][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[13][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%13;
					if(map[i][j].marks){
						map[i][j].time++;
						if(map[i][j].time>=40){
							map[i][j].time=0;
							hit.flag=1,hit.x=map[i][j].x+30,hit.y=map[i][j].y+20,hit.i=hit.j=0;
							vec.push_back(hit);
						}
					}
				}
				/*else if(map[i][j].i==7){//potato
				GetObject(b[14][map[i][j].j],sizeof(BITMAP),&bp);
				SelectObject(bufdc,b[14][map[i][j].j]);
				TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,255,0));
				map[i][j].j=(map[i][j].j+1)%8;
				}*/
				else if(map[i][j].i==8){//repeater
					AlphaBmp(mdc,e[9][0],map[i][j].x-10,map[i][j].y+67,80,hrgn[11][0],RGB(255,255,255));
					GetObject(b[15][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[15][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%15;
					if(map[i][j].marks){
						map[i][j].time++;
						if(map[i][j].repeater){
							if(map[i][j].time>=8){
								map[i][j].time=0;
								hit.flag=1,hit.x=map[i][j].x+30,hit.y=map[i][j].y+20,hit.i=hit.j=0;
								vec.push_back(hit);
								map[i][j].repeater=0;
							}
						}
						else {
							if(map[i][j].time>=32){
								map[i][j].time=0;
								hit.flag=1,hit.x=map[i][j].x+30,hit.y=map[i][j].y+20,hit.i=hit.j=0;
								vec.push_back(hit);
								map[i][j].repeater=1;
							} 
						}
					}
				}
				else if(map[i][j].i==9){//snowpea
					AlphaBmp(mdc,e[9][0],map[i][j].x-10,map[i][j].y+67,80,hrgn[11][0],RGB(255,255,255));
					GetObject(b[16][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[16][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%15;
					if(map[i][j].marks){
						map[i][j].time++;
						if(map[i][j].time>=40){
							map[i][j].time=0;
							hit.flag=4,hit.x=map[i][j].x+30,hit.y=map[i][j].y+20,hit.i=hit.j=0;
							vec.push_back(hit);
						}
					}
				}
				else if(map[i][j].i==10){//lajiao
					AlphaBmp(mdc,e[9][0],map[i][j].x-10,map[i][j].y+82,80,hrgn[11][0],RGB(255,255,255));
					GetObject(b[12][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[12][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%8;
					if(map[i][j].j==0)
						map[i][j].i=11;
				}
				else if(map[i][j].i==11){
					for(it1=Zombie.begin();it1!=Zombie.end();it1++)
						if((*it1).stata!=3&&(*it1).y==map[i][j].y-30&&(*it1).x<850){
							(*it1).stata=2;
							(*it1).j=0;
							(*it1).i=7;
						}
						GetObject(b[4][map[i][j].j],sizeof(BITMAP),&bp);
						SelectObject(bufdc,b[4][map[i][j].j]);
						TransparentBlt(mdc,150,map[i][j].y+plant[map[i][j].i].y-35,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
						map[i][j].j=(map[i][j].j+1)%8;
						if(map[i][j].j==0)
							map[i][j].i=-1;
				}
				else if(map[i][j].i==12){//gangci
					GetObject(b[26][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[26][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%8;
				}
				else if(map[i][j].i==13){//yintao
					AlphaBmp(mdc,e[9][0],map[i][j].x-10,map[i][j].y+82,80,hrgn[11][0],RGB(255,255,255));
					GetObject(b[27][map[i][j].j],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[27][map[i][j].j]);
					TransparentBlt(mdc,map[i][j].x+plant[map[i][j].i].x,map[i][j].y+plant[map[i][j].i].y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					map[i][j].j=(map[i][j].j+1)%7;
					if(map[i][j].j==0)
						map[i][j].i=14;
				}
				else if(map[i][j].i==14){
					if(map[i][j].j==1){
					for(it1=Zombie.begin();it1!=Zombie.end();it1++)
					{
						int l,r;
						if(j==1){
							l=map[i][j].x-100;
							r=map[i][j+1].x;
						}
						else if(j==9){
							l=map[i][j-1].x-100;
							r=map[i][j].x+82;
						}
						else{
							l=map[i][j-1].x-100;
							r=map[i][j+1].x;
						}
						if((*it1).stata!=3&&((*it1).y==map[i][j].y-30||(*it1).y==map[i-1][j].y-30||(*it1).y==map[i+1][j].y-30)&&((*it1).x>l)&&((*it1).x<r)){
							(*it1).stata=2;
							(*it1).j=0;
							(*it1).i=7;
						}
					}
					}
						GetObject(b[28][1],sizeof(BITMAP),&bp);
						SelectObject(bufdc,b[28][1]);
						TransparentBlt(mdc,map[i][j].x,map[i][j].y+plant[map[i][j].i].y-115,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,0,0));
						map[i][j].j=(map[i][j].j+1)%12;
						if(map[i][j].j==0)
							map[i][j].i=-1;
				}
			}
			for(it1=Zombie.begin();it1!=Zombie.end();){//画僵尸
				if((*it1).x+72<0){//GAME OVER
					mciSendString("stop .\\re\\gnite.wav",NULL,0,NULL);
					START=11;
					mciSendString("play .\\re\\lose.wav",NULL,0,NULL);
					//PlaySound("c:\\porridge\\lose.wav",NULL,SND_ASYNC);
				}
				if((*it1).flag==3&&((*it1).slow==1||(*it1).slow==2))
					(*it1).v=2;
				else if((*it1).slow==1){//寒冰减速
					(*it1).slow=2;
					(*it1).v=0;
				}
				else if((*it1).slow==2){
					(*it1).slow=1;
					(*it1).v=1;
				}
				x=(((*it1).x-150+20+82+82)/82);
				y=(((*it1).y-40+100)/100);
				if(x>=1&&x<=9&&y>=1&&y<=5)//吃植物
					if(map[y][x].i!=-1){
						if(map[y][x].i!=4&&map[y][x].i!=11&&map[y][x].i!=12&&map[y][x].i!=14){
							if((*it1).stata==0){
								(*it1).stata=6;
								(*it1).i=1;
								(*it1).j=0;
								(*it1).v=0;
							}
							else if((*it1).stata==4){
								(*it1).stata=7;
								(*it1).i=5;
								(*it1).j=0;
								(*it1).v=0;
							}
						}
						else if(map[y][x].i==4) 
							(*it1).life-=1;
						else if(map[y][x].i==12) 
							(*it1).life-=2;
					}
					else{
						if((*it1).stata==6){
							(*it1).stata=0;
							(*it1).i=4;
							(*it1).j=0;
							if((*it1).flag==1||((*it1).flag==2))
								(*it1).v=1;
							else if((*it1).flag==3)
								(*it1).v=5;
						}
						else if((*it1).stata==7){
							(*it1).stata=4;
							(*it1).i=6;
							(*it1).j=0;
							if((*it1).flag==1||((*it1).flag==2))
								(*it1).v=1;
							else if((*it1).flag==3)
								(*it1).v=5;
						}
					}
					if((*it1).life<0&&((*it1).stata==0||(*it1).stata==6)){
						(*it1).stata=4;
						(*it1).i=6;
						(*it1).j=0;
						(*it1).headj=0;
					}
					if((*it1).stata==2){//burn
						/*if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+100,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+65,(*it1).y+127,50,hrgn[11][0],RGB(255,255,255));
						*/
						GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
						SelectObject(bufdc,c[(*it1).i][(*it1).j]);
						TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
						(*it1).j++;
						if((*it1).j==20){
							znum[((*it1).y+60)/100]--;
							Zombie.erase(it1);
						}
						else
							it1++;
					}
					else if((*it1).stata==3){//fall
						if((*it1).flag==1||(*it1).flag==2){
							if((*it1).j<10){
								GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
								SelectObject(bufdc,c[(*it1).i][(*it1).j]);
								TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
								(*it1).j++;
								it1++;
							}
							else if((*it1).j<30){
								GetObject(c[(*it1).i][9],sizeof(BITMAP),&bp);
								SelectObject(bufdc,c[(*it1).i][9]);
								TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
								(*it1).j++;
								it1++;
							}
							else{
								znum[((*it1).y+60)/100]--;
								Zombie.erase(it1);
							}
						}
						else if((*it1).flag==3){
							if((*it1).j<7){
								GetObject(e[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
								SelectObject(bufdc,e[(*it1).i][(*it1).j]);
								TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
								(*it1).j++;
								it1++;
							}
							else if((*it1).j<30){
								GetObject(e[(*it1).i][6],sizeof(BITMAP),&bp);
								SelectObject(bufdc,e[(*it1).i][6]);
								TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
								(*it1).j++;
								it1++;
							}
							else{
								znum[((*it1).y+60)/100]--;
								Zombie.erase(it1);
							}
						}
						
					}
					else if((*it1).stata==4){//diewalk
						if((*it1).flag==1){
							GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,c[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%18;
							(*it1).x=(*it1).x-(*it1).v;
						}
						else if((*it1).flag==2){
							GetObject(d[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,d[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%12;
							(*it1).x=(*it1).x-(*it1).v;
						}
						else if((*it1).flag==3){
							GetObject(e[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,e[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).t=((*it1).t+1)%2;
							if((*it1).t==0){
								if((*it1).j<=8)
									(*it1).x=(*it1).x-(*it1).v;
								(*it1).j=((*it1).j+1)%10;
							}
						}
						if((*it1).headj<12){
							GetObject(c[3][(*it1).headj],sizeof(BITMAP),&bp);
							SelectObject(bufdc,c[3][(*it1).headj]);
							TransparentBlt(mdc,(*it1).x-(*it1).headj*(*it1).v+50,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).headj=(*it1).headj+1;
						}
						(*it1).life=(*it1).life-5;
						if((*it1).life<-200){
							(*it1).stata=3;
							(*it1).i=2;
							(*it1).j=0;
						}
						it1++;
					}
					else if((*it1).stata==6){//eat
						/*if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+80,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+50,(*it1).y+137,50,hrgn[11][0],RGB(255,255,255));
						*/
						if((*it1).flag==1){
							GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,c[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%21;
						}
						else if((*it1).flag==2){
							GetObject(d[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,d[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%11;
						}
						else if((*it1).flag==3){
							GetObject(e[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,e[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%11;
						}
						map[y][x].life-=(*it1).attack;
						//if(EAT==0){
							mciSendString("play .\\re\\eat0.wav",NULL,0,NULL);
						//	EAT=1;
						//}
						//else if(EAT==1){
						//	mciSendString("play .\\re\\eat1.wav",NULL,0,NULL);
						//	EAT=2;
						//}
						//else{
						//	mciSendString("play .\\re\\eat2.wav",NULL,0,NULL);
						//	EAT=0;
						//}
						//PlaySound("c:\\porridge\\eat.wav",NULL,SND_ASYNC);
						it1++;
					}
					else if((*it1).stata==7){//nohead eat
						/*if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+80,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+25,(*it1).y+137,50,hrgn[11][0],RGB(255,255,255));
						*/
						//if(EAT==0){
							mciSendString("play .\\re\\eat0.wav",NULL,0,NULL);
						//	EAT=1;
						//}
						//else if(EAT==1){
						//	mciSendString("play .\\re\\eat1.wav",NULL,0,NULL);
						//	EAT=2;
						//}
						//else{
						//	mciSendString("play .\\re\\eat2.wav",NULL,0,NULL);
						//	EAT=0;
						
						if((*it1).flag==1){
							GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,c[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%11;
						}
						else if((*it1).flag==2){
							GetObject(d[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,d[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%11;
						}
						else if((*it1).flag==3){
							GetObject(e[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,e[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%10;
						}
						if((*it1).headj<12){
							GetObject(c[3][(*it1).headj],sizeof(BITMAP),&bp);
							SelectObject(bufdc,c[3][(*it1).headj]);
							TransparentBlt(mdc,(*it1).x-(*it1).headj*(*it1).v+50,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).headj=(*it1).headj+1;
						}
						(*it1).life=(*it1).life-5;
						if((*it1).life<-200){
							(*it1).stata=3;
							(*it1).i=2;
							(*it1).j=0;
						}
						//(*it1).x=(*it1).x-(*it1).v;
						it1++;
					}
					else if((*it1).stata==0){//walk
						/*if((*it1).flag==1)
						    AlphaBmp(mdc,e[9][0],(*it1).x+70,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else if((*it1).flag==2)
							AlphaBmp(mdc,e[9][0],(*it1).x+100,(*it1).y+117,50,hrgn[11][0],RGB(255,255,255));
						else
							AlphaBmp(mdc,e[9][0],(*it1).x+65,(*it1).y+127,50,hrgn[11][0],RGB(255,255,255));
						*/
						if((*it1).flag==1){
							GetObject(c[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,c[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%31;
							(*it1).x=(*it1).x-(*it1).v;
						}
						else if((*it1).flag==2){
							GetObject(d[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,d[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).j=((*it1).j+1)%12;
							(*it1).x=(*it1).x-(*it1).v;
						}
						else if((*it1).flag==3){
							GetObject(e[(*it1).i][(*it1).j],sizeof(BITMAP),&bp);
							SelectObject(bufdc,e[(*it1).i][(*it1).j]);
							TransparentBlt(mdc,(*it1).x,(*it1).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
							(*it1).t=((*it1).t+1)%2;
							if((*it1).t==0){
								if((*it1).j<=9)
									(*it1).x=(*it1).x-(*it1).v;
								(*it1).j=((*it1).j+1)%11;
							}
						}
						it1++;
					}
			}
			sort(Zombie.begin(),Zombie.end());
			for(it=vec.begin();it!=vec.end();){//画粒子
				if((*it).x>1000){//粒子出界
					vec.erase(it);
				}
				else if((*it).flag==1){
					x=((*it).x-150)/82+1;//判断遇到fire
					y=((*it).y-70)/100+1;
					if(x>9)
						x=9;
					if(y>5)
						y=5;
					if(x!=(*it).j||y!=(*it).i)
						if(map[y][x].i==5&&(*it).x>map[y][x].x&&(*it).x<=map[y][x].x+82&&(*it).y>map[y][x].y&&(*it).y<=map[y][x].y+100)
							(*it).flag=2;
						
						GetObject(b[20][0],sizeof(BITMAP),&bp);
						SelectObject(bufdc,b[20][0]);
						TransparentBlt(mdc,(*it).x,(*it).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
						for(it1=Zombie.begin();it1!=Zombie.end();it1++)//体积碰撞
							if((*it1).stata!=3&&(*it).x>(*it1).x+30&&(*it).y>(*it1).y&&(*it).y<(*it1).y+80){
								if((*it1).stata==0||(*it1).stata==6)
									(*it1).life=(*it1).life-10;
								(*it).flag=6;
								break;
							}
							(*it).x+=10;
							it++;
				}
				else if((*it).flag==2){
					(*it).flag=3;
					GetObject(b[22][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[22][0]);
					TransparentBlt(mdc,(*it).x,(*it).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					for(it1=Zombie.begin();it1!=Zombie.end();it1++)//体积碰撞
						if((*it1).stata!=3&&(*it).x>(*it1).x+30&&(*it).y>(*it1).y&&(*it).y<(*it1).y+80){
							if((*it1).stata==0||(*it1).stata==6)
								(*it1).life=(*it1).life-20;
							(*it).flag=5;
							break;
						}
						(*it).x+=10;
						it++;
				}
				else if((*it).flag==3){
					(*it).flag=2;
					GetObject(b[22][1],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[22][1]);
					TransparentBlt(mdc,(*it).x,(*it).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					for(it1=Zombie.begin();it1!=Zombie.end();it1++)//体积碰撞
						if((*it1).stata!=3&&(*it).x>(*it1).x+30&&(*it).y>(*it1).y&&(*it).y<(*it1).y+80){
							if((*it1).stata==0||(*it1).stata==6)
								(*it1).life=(*it1).life-20;
							(*it).flag=5;
							break;
						}
						(*it).x+=10;
						it++;
				}
				else if((*it).flag==4){
					x=((*it).x-150)/82+1;//判断遇到fire
					y=((*it).y-70)/100+1;
					if(x>9)
						x=9;
					if(y>5)
						y=5;
					if(x!=(*it).j||y!=(*it).i)
						if(map[y][x].i==5&&(*it).x>map[y][x].x&&(*it).x<=map[y][x].x+82&&(*it).y>map[y][x].y&&(*it).y<=map[y][x].y+100)
						{
							(*it).i=y,(*it).j=x;
							(*it).flag=1;
						}
						GetObject(b[21][0],sizeof(BITMAP),&bp);
						SelectObject(bufdc,b[21][0]);
						TransparentBlt(mdc,(*it).x,(*it).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
						for(it1=Zombie.begin();it1!=Zombie.end();it1++)//体积碰撞
							if((*it1).stata!=3&&(*it).x>(*it1).x+30&&(*it).y>(*it1).y&&(*it).y<(*it1).y+80){
								if((*it1).stata==0||(*it1).stata==6)
									(*it1).life=(*it1).life-10;
								if(map[y][x].i==-1)
								   (*it1).slow=1;
								(*it).flag=6;
								break;
							}
							(*it).x+=10;
							it++;
				}
				else if((*it).flag==5){
					GetObject(b[2][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[2][0]);
					TransparentBlt(mdc,(*it).x+25,(*it).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					(*it).flag=7;
				}
				else if((*it).flag==7){
					mciSendString("play .\\re\\firepea.wav",NULL,0,NULL);
					GetObject(b[2][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[2][0]);
					TransparentBlt(mdc,(*it).x+25,(*it).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					vec.erase(it);
				}
				else if((*it).flag==6){
					mciSendString("play .\\re\\pea.wav",NULL,0,NULL);
					GetObject(b[20][1],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[20][1]);
					TransparentBlt(mdc,(*it).x+25,(*it).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					vec.erase(it);
				}
			}
			GetObject(b[28][0],sizeof(BITMAP),&bp);//画阳光盒
			SelectObject(bufdc,b[28][0]);
			TransparentBlt(mdc,0,60,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
			if(CLICK&&cz.inback&&!MARKX){//判断是否选中阳光
				if(mousex>=sun.x+10&&mousex<=sun.x+70&&mousey>=sun.y+10&&mousey<=sun.y+70){
					ssun.x=sun.x,ssun.y=sun.y,ssun.j=0,ssun.vx=sun.x/10,ssun.vy=(sun.y-30)/10;
					sunsun.push_back(ssun);
					//sunnum.num+=25;
					sun.x=9999;
					CLICK=0;
					//mciSendString("stop .\\re\\clicksun.wav",NULL,0,NULL);
					   mciSendString("play .\\re\\clicksun.wav",NULL,0,NULL);
					//PlaySound("c:\\porridge\\clicksun.wav",NULL,SND_ASYNC);
				}
				for(i=1;i<=5;i++)
					for(j=1;j<=9;j++)
						if(map[i][j].have){
							if(mousex>=map[i][j].x-20&&mousex<=map[i][j].x+60&&mousey>=map[i][j].y+30&&mousey<=map[i][j].y+100){
								ssun.x=map[i][j].x-30,ssun.y=map[i][j].y+30,ssun.j=0,ssun.vx=ssun.x/10,ssun.vy=(ssun.y-30)/10;
								sunsun.push_back(ssun);
								map[i][j].have=0;
								//sunnum.num+=25;
								map[i][j].time=0;
								
					   mciSendString("play .\\re\\clicksun.wav",NULL,0,NULL);			
							}
						}
			}
			if(cz.inback&&CLICK){
				if(!MARKX)
					for(i=0;i<10;i++)//判断哪一种植物被选中
						if(sunnum.num>=tubiao[i].price&&tubiao[i].bright&&mousex>=tubiao[i].x&&mousex<=tubiao[i].x+100&&mousey>=tubiao[i].y&&mousey<=tubiao[i].y+60){
							tubiao[i].isclick=true;
							which=i;
							MARKX=1;
							break;
						}
						if(MARKAF)//判断哪一种植物种下
							for(i=1;i<=5;i++){
								for(j=1;j<=9;j++){
									if(AF.i==12&&map[i][j].i==4&&mousex>=map[i][j].x&&mousex<map[i][j].x+82&&mousey>=map[i][j].y&&mousey<map[i][j].y+106){
									mciSendString("play .\\re\\zhongxia.wav",NULL,0,NULL);
										map[i][j].i=AF.i;//第AF.I种植物安放了
											map[i][j].life=999999;
										map[i][j].j=0;
										AF.ANFANG=0;
										MARKAF=0;
										tubiao[8].isclick=false;
										sunnum.num-=tubiao[8].price;
										tubiao[8].bright=0;
										tubiao[8].time=0;
										MARKX=0;
									}
									else if(AF.i!=12&&map[i][j].i==-1&&mousex>=map[i][j].x&&mousex<map[i][j].x+82&&mousey>=map[i][j].y&&mousey<map[i][j].y+106){
										//mciSendString("play .\\re\\clicksun.wav",NULL,0,NULL);
										mciSendString("play .\\re\\zhongxia.wav",NULL,0,NULL);
										map[i][j].i=AF.i;//第AF.I种植物安放了
										if(AF.i==0){//向日葵准备生产
											map[i][j].time=0;
											map[i][j].marks=1;
											map[i][j].life=1000;
										}
										else if(AF.i==1)
											map[i][j].life=13000;
										else if(AF.i==4)
											map[i][j].life=999999;
										else if(AF.i==5)
											map[i][j].life=1000;
										else if(AF.i==6){//豌豆射手生产
											map[i][j].time=0;
											map[i][j].marks=0;
											map[i][j].life=1000;
											pnum[i]++;
										}
										else if(AF.i==9){//寒冰射手生产
											map[i][j].time=0;
											map[i][j].marks=0;
											map[i][j].life=1000;
											pnum[i]++;
										}
										else if(AF.i==8){//repeater生产
											map[i][j].time=0;
											map[i][j].marks=0;
											map[i][j].repeater=0;
											map[i][j].life=1000;
											pnum[i]++;
										}
										else if(AF.i==10)
											map[i][j].life=1000000;
										else if(AF.i==13)
											map[i][j].life=1000000;
										map[i][j].j=0;
										AF.ANFANG=0;
										MARKAF=0;
										for(k=0;k<10;k++){
											if(tubiao[k].isclick){
												tubiao[k].isclick=false;
												break;
											}
										}
										sunnum.num-=tubiao[k].price;
										tubiao[k].bright=0;
										tubiao[k].time=0;
										MARKX=0;
									}
									if(AF.ANFANG==0)
										break;
								}
								if(AF.ANFANG==0)
									break;
							}
			}
			for(i=0;i<10;i++){//画图标
				tubiao[i].time++;
				if(tubiao[i].time>=tubiao[i].cd)//判断cd
					tubiao[i].bright=1;
				if(tubiao[i].bright){
					SelectObject(bufdc,btb[tubiao[i].plant][0]);
					TransparentBlt(mdc,tubiao[i].x,tubiao[i].y,bmtb[tubiao[i].plant][0].bmWidth,bmtb[tubiao[i].plant][0].bmHeight,bufdc,0,0,bmtb[tubiao[i].plant][0].bmWidth,bmtb[tubiao[i].plant][0].bmHeight,RGB(255,255,255));
				}
				else{		
					SelectObject(bufdc,btb[tubiao[i].plant][1]);
					TransparentBlt(mdc,tubiao[i].x,tubiao[i].y,bmtb[tubiao[i].plant][1].bmWidth,bmtb[tubiao[i].plant][1].bmHeight,bufdc,0,0,bmtb[tubiao[i].plant][1].bmWidth,bmtb[tubiao[i].plant][1].bmHeight,RGB(255,255,255));
					px=tubiao[i].time*50*60/tubiao[i].cd;
					if(px>60){
						tubiao[i].bright=1;
					}
					SelectObject(bufdc,btb[tubiao[i].plant][0]);
					TransparentBlt(mdc,tubiao[i].x,tubiao[i].y+(bmtb[tubiao[i].plant][0].bmHeight-px),bmtb[tubiao[i].plant][0].bmWidth,px,bufdc,0,bmtb[tubiao[i].plant][0].bmHeight-px,bmtb[tubiao[i].plant][0].bmWidth,px,RGB(255,255,255));	
				}
				if(sunnum.num<tubiao[i].price){
					SelectObject(bufdc,btb[tubiao[i].plant][1]);
					TransparentBlt(mdc,tubiao[i].x,tubiao[i].y,bmtb[tubiao[i].plant][1].bmWidth,bmtb[tubiao[i].plant][1].bmHeight,bufdc,0,0,bmtb[tubiao[i].plant][1].bmWidth,bmtb[tubiao[i].plant][1].bmHeight,RGB(255,255,255));
				}
			}
			GetObject(b[19][1],sizeof(BITMAP),&bp);//画铲子和铲子盒
			SelectObject(bufdc,b[19][1]);
			TransparentBlt(mdc,czback.x,czback.y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
			GetObject(b[19][0],sizeof(BITMAP),&bp);
			SelectObject(bufdc,b[19][0]);
			if(CLICK&&cz.inback&&mousex>=20&&mousex<=94&&mousey>=110&&mousey<=142&&!AF.ANFANG)
				cz.inback=false;
			if(cz.inback)
				TransparentBlt(mdc,cz.x,cz.y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
			else{
				cz.outx=movex;
				cz.outy=movey;
				TransparentBlt(mdc,cz.outx-38,cz.outy-17,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
				if(CLICK){//铲掉植物
					for(i=1,numplant=0;i<=5;i++)
						for(j=1;j<=9;j++){
							if(map[i][j].i!=-1&&mousex-38>=map[i][j].x&&mousex-38<=map[i][j].x+82&&mousey>=map[i][j].y&&mousey<=map[i][j].y+106){
								mciSendString("play .\\re\\chanzi.wav",NULL,0,NULL);
								if(map[i][j].i==6||map[i][j].i==8||map[i][j].i==9)
									pnum[i]--;
								map[i][j].i=-1;
								map[i][j].j=0;
								map[i][j].marks=0;			
								cz.inback=true;
							}
						}
				}
			}
			if(MARKX){//画半透明植物
				for(i=1;i<=5;i++)
					for(j=1;j<=9;j++)
						if(map[i][j].i==-1)
							if(movex>=map[i][j].x&&movex<map[i][j].x+82&&movey>=map[i][j].y&&movey<map[i][j].y+106){
								if(AF.i==0){
									//hrgn=BitmapToRgn(bit[1][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[1][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[1][0],RGB(0,0,0));
									//DeleteObject(hrgn);
								}
								else if(AF.i==1){
									//hrgn=BitmapToRgn(bit[3][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[3][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[3][0],RGB(0,0,0));
								}
								else if(AF.i==4){
									//hrgn=BitmapToRgn(bit[2][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[2][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[2][0],RGB(0,0,0));
								}
								else if(AF.i==5){
									//hrgn=BitmapToRgn(bit[4][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[4][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[4][0],RGB(0,0,0));
								}
								else if(AF.i==6){
									//hrgn=BitmapToRgn(bit[6][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[6][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[6][0],RGB(0,0,0));
								}
								else if(AF.i==8){
									//hrgn=BitmapToRgn(bit[7][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[7][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[7][0],RGB(0,0,0));
								}
								else if(AF.i==9){
									//hrgn=BitmapToRgn(bit[8][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[8][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[8][0],RGB(0,0,0));
								}
								else if(AF.i==10){
									//hrgn=BitmapToRgn(bit[5][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[5][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[5][0],RGB(0,0,0));
								}
								else if(AF.i==13){
									//hrgn=BitmapToRgn(bit[5][0],RGB(0,0,0));
									AlphaBmp(mdc,bit[10][0],map[i][j].x+plant[AF.i].x,map[i][j].y+plant[AF.i].y,150,hrgn[10][0],RGB(0,0,0));
								}
							}
			}
			for(i=0;i<10;i++)//画正在安放的植物
				if(tubiao[i].isclick&&tubiao[i].plant==0){
					GetObject(b[17][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[17][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=0;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==1){
					GetObject(b[23][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[23][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=1;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==4){
					GetObject(b[10][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[10][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=4;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==5){
					GetObject(b[11][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[11][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=5;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==6){
					GetObject(b[13][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[13][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=6;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==8){
					GetObject(b[15][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[15][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=8;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==9){
					GetObject(b[16][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[16][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=9;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==10){
					GetObject(b[12][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[12][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=10;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==12){
					GetObject(b[26][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[26][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=12;
				}
				else if(tubiao[i].isclick&&tubiao[i].plant==13){
					GetObject(b[27][0],sizeof(BITMAP),&bp);
					SelectObject(bufdc,b[27][0]);
					TransparentBlt(mdc,movex-bp.bmWidth/2,movey-bp.bmHeight,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
					AF.ANFANG=1;
					AF.i=13;
				}
				suntime++;//画随机产生的阳光
				if(suntime>=160){
					suntime=0;
					sun.x=xx[(K++)%4];
					sun.y=-30;
					sun.endy=yy[(K)%3];
				}
				if(sun.x!=9999){
					if(sun.y<=sun.endy){
						GetObject(b[29][sun.j],sizeof(BITMAP),&bp);
						SelectObject(bufdc,b[29][sun.j]);
						TransparentBlt(mdc,sun.x,sun.y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
						sun.y=sun.y+7;
						tt=suntime;
					}
					else{
						LIMIT=150+(160-suntime)*105/(160-tt);
						AlphaBmp(mdc,bit[0][sun.j],sun.x,sun.y,LIMIT,hrgn[0][sun.j],RGB(0,0,0));
					}	
					sun.j=(sun.j+1)%21;
				}
				for(it2=sunsun.begin();it2!=sunsun.end();){//paint sun back
					if((*it2).x<60&&(*it2).y<40){
						sunsun.erase(it2);
						sunnum.num+=25;
					}
					else{
						GetObject(b[29][(*it2).j],sizeof(BITMAP),&bp);
						SelectObject(bufdc,b[29][(*it2).j]);
						TransparentBlt(mdc,(*it2).x,(*it2).y,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(0,0,0));
						(*it2).x-=(*it2).vx;
						(*it2).y-=(*it2).vy;
						(*it2).j=((*it2).j+1)%21;
						it2++;
					}
				}
				zombiet++;
				if(GAMETIME<3600){
					if(zombiet>=TIME){
						if(TIME==200)
							mciSendString("play .\\re\\start.wav",NULL,0,NULL);
						//PlaySound("c:\\porridge\\start.wav",NULL,SND_ASYNC);
						if(TIME>400)
							TIME=TIME-40;
						else if(TIME>40)
							TIME=TIME-100;
						else
							TIME=40;
						zombie.flag=1;
						if(zombie.flag==1||zombie.flag==2){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=100,zombie.v=1,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						else if(zombie.flag==3){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=200,zombie.v=5,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						zbj=(zbj+1)%20;
						Zombie.push_back(zombie);
						zombiet=0;
					}
				}
				else if(GAMETIME>=3600&&GAMETIME<3640){//一大波僵尸
					if(GAMETIME==3610)
						mciSendString("play .\\re\\first.wav",NULL,0,NULL);
					GetObject(a[3][15],sizeof(BITMAP),&bp);
					SelectObject(bufdc,a[3][15]);
					TransparentBlt(mdc,300,200,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
					TIME=20;
					fuck=1;
				}
				else if(GAMETIME>=3640&&GAMETIME<3840){
					if(zombiet>=TIME){
						zombie.flag=1;
						if(zombie.flag==1||zombie.flag==2){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=100,zombie.v=1,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						else if(zombie.flag==3){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=200,zombie.v=5,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						zbj=(zbj+1)%20;
						Zombie.push_back(zombie);
						if(fuck){
							zombie.flag=2,zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=100,zombie.v=1,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
							zbj=(zbj+1)%20;
							Zombie.push_back(zombie);
							fuck=0;
						}
						zombiet=0;
					}
				}
				else if(GAMETIME>=3840&&GAMETIME<4040)
					TIME=25;
				else if(GAMETIME>=4040&&GAMETIME<6900){
					if(zombiet>=TIME){
						zombie.flag=zflag[z++];
						if(z==10)
							z=0;
						if(zombie.flag==1||zombie.flag==2){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=100,zombie.v=1,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						else if(zombie.flag==3){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=200,zombie.v=5,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						zbj=(zbj+1)%20;
						Zombie.push_back(zombie);
						zombiet=0;
					}
				}
				else if(GAMETIME>=6900&&GAMETIME<6940){//最后一波
					if(GAMETIME==6910)
						mciSendString("play .\\re\\last.wav",NULL,0,NULL);
					//PlaySound("c:\\porridge\\last.wav",NULL,SND_ASYNC);
					GetObject(a[3][14],sizeof(BITMAP),&bp);
					SelectObject(bufdc,a[3][14]);
					TransparentBlt(mdc,300,200,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
					TIME=5;
					fuck=1;
				}
				else if(GAMETIME>=7000&&GAMETIME<7200){
					if(zombiet>=TIME){
						zombie.flag=3;
						if(zombie.flag==1||zombie.flag==2){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=100,zombie.v=1,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						else if(zombie.flag==3){
							zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=200,zombie.v=5,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,zombie.t=0,znum[(zombiey[zbj]+60)/100]++;
						}
						zbj=(zbj+1)%20;
						Zombie.push_back(zombie);
						if(fuck){
							zombie.flag=2,zombie.x=980,zombie.y=zombiey[zbj],zombie.i=4;zombie.j=0,zombie.life=250,zombie.v=1,zombie.stata=0,zombie.headj=0,zombie.slow=0,zombie.attack=15,znum[(zombiey[zbj]+60)/100]++;
							zbj=(zbj+1)%20;
							Zombie.push_back(zombie);
							fuck=0;
						}
						zombiet=0;
					}
				}
				else if(GAMETIME>=7200){//判断win
					if(Zombie.empty()){
						START=13;
						mciSendString("stop .\\re\\gnite.wav",NULL,0,NULL);
					}
				}
				GetObject(a[3][9],sizeof(BITMAP),&bp);
				SelectObject(bufdc,a[3][9]);
				TransparentBlt(mdc,800,568,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,0,0));
				if(GAMETIME<=500)
					px=0;
				else if(GAMETIME<=7200&&GAMETIME>500)
					px=(GAMETIME-500)*145/6700;
				else
					px=145;
				if(GAMETIME>=500){
					GetObject(a[3][10],sizeof(BITMAP),&bp);
					SelectObject(bufdc,a[3][10]);
					TransparentBlt(mdc,800+151-px,568,px+6,bp.bmHeight,bufdc,151-px,0,px+6,bp.bmHeight,RGB(255,0,0));
				}
				GetObject(a[3][8],sizeof(BITMAP),&bp);
				SelectObject(bufdc,a[3][8]);
				TransparentBlt(mdc,867,560,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
				GetObject(a[3][8],sizeof(BITMAP),&bp);
				SelectObject(bufdc,a[3][8]);
				TransparentBlt(mdc,800,560,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
				GetObject(a[3][13],sizeof(BITMAP),&bp);
				SelectObject(bufdc,a[3][13]);
				TransparentBlt(mdc,800+143-px,555,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,0,0));
				
				hf_black=CreateFont(20,0,0,0,FW_HEAVY,0,0,0,GB2312_CHARSET,OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,NULL);
				for(i=0;i<10;i++){
					SetTextColor(mdc,RGB(0,0,0));//显示花费
					SelectObject(mdc,hf_black);
					SetBkMode(mdc, TRANSPARENT);
					GetTextMetrics(mdc,&tm);
					sprintf(st,"%d",tubiao[i].price);
					nnum=tubiao[i].price;
					len=0;
					do{
						len++;
						nnum=nnum/10;
					}while(nnum);
					TextOut(mdc,tubiao[i].x+63,tubiao[i].y+10,st,len);
				}
				//hf_black=CreateFont(20,0,0,0,FW_HEAVY,0,0,0,GB2312_CHARSET,OUT_DEFAULT_PRECIS,
				//	CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,NULL);
				SetTextColor(mdc,RGB(255,0,0));//显示当前阳光数量
				SelectObject(mdc,hf_black);
				SetBkMode(mdc, TRANSPARENT);
				GetTextMetrics(mdc,&tm);
				sprintf(st,"%d",sunnum.num);
				nnum=sunnum.num;
				len=0;
				do{
					len++;
					nnum=nnum/10;
				}while(nnum);
				TextOut(mdc,sunnum.x,sunnum.y,st,len);
				//sprintf(st,"%d,%d,%d,%d,%d %d,%d,%d,%d,%d %d,%d",pnum[1],pnum[2],pnum[3],pnum[4],pnum[5],znum[1],znum[2],znum[3],znum[4],znum[5],map[4][1].time,map[4][1].marks);
				//TextOut(mdc,100,570,st,45);
				GetTextMetrics(mdc,&tm);
				}
				else if(START==11){
					SelectObject(bufdc,b[9][0]);
					BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
					GetObject(a[3][12],sizeof(BITMAP),&bp);
					SelectObject(bufdc,a[3][12]);
					TransparentBlt(mdc,200,100,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
					BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
					if(RCLICK)
						START=1;
				}
				else if(START==12){
					SelectObject(bufdc,b[9][0]);
					BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
					GetObject(a[3][1],sizeof(BITMAP),&bp);
					SelectObject(bufdc,a[3][1]);
					TransparentBlt(mdc,200,100,bp.bmWidth,bp.bmHeight,bufdc,0,0,bp.bmWidth,bp.bmHeight,RGB(255,255,255));
					BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
					if(RCLICK)
						START=1;
				}
				else if(START==13){
					SelectObject(bufdc,b[9][0]);
					BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
					SelectObject(bufdc,c[10][0]);
					BitBlt(mdc,100,0,1000,600,bufdc,0,0,SRCCOPY);
					BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
					if(CLICK)
						START=14;
				}
				else if(START==14){
					SelectObject(bufdc,b[9][0]);
					BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
					SelectObject(bufdc,c[10][1]);
					BitBlt(mdc,100,0,1000,600,bufdc,0,0,SRCCOPY);
					BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
					if(CLICK)
						START=15;
				}
				else if(START==15){
					SelectObject(bufdc,b[9][0]);
					BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
					SelectObject(bufdc,c[10][2]);
					BitBlt(mdc,100,0,1000,600,bufdc,0,0,SRCCOPY);
					BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
					if(CLICK)
						START=16;
				}
				else if(START==16){
					SelectObject(bufdc,b[9][0]);
					BitBlt(mdc,0,0,1000,600,bufdc,100,0,SRCCOPY);
					SelectObject(bufdc,c[10][3]);
					BitBlt(mdc,100,0,1000,600,bufdc,0,0,SRCCOPY);
					BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
					if(CLICK)
						START=13;
				}
				BitBlt(hdc,0,0,1000,600,mdc,0,0,SRCCOPY);
				tPre = GetTickCount();     //记录此次绘图时间
				CLICK=0;
				RCLICK=0;
				
				
}
//****消息处理函数***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,j;
	switch (message)
	{
	case WM_LBUTTONDOWN:
		CLICK=1;
		if(AF.ANFANG)
			MARKAF=1;
		mousex=LOWORD(lParam);
		mousey=HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		RCLICK=1;
		break;
	case WM_MOUSEMOVE:
		movex=LOWORD(lParam);
		movey=HIWORD(lParam);
		break;
	case WM_DESTROY://窗口结束消息，撤销各种DC
		for(i=0;i<30;i++){
			for(j=0;j<30;j++)
				DeleteObject(b[i][j]);
		}
		for(i=0;i<20;i++){
			for(j=0;j<30;j++)
				DeleteObject(bit[i][j]);
		}
		for(i=0;i<20;i++){
			for(j=0;j<30;j++)
				DeleteObject(btb[i][j]);
		}
		for(i=0;i<20;i++){
			for(j=0;j<40;j++)
				DeleteObject(c[i][j]);
		}
		for(i=0;i<10;i++){
			for(j=0;j<20;j++)
				DeleteObject(a[i][j]);
		}
		for(i=0;i<10;i++){
			for(j=0;j<20;j++)
				DeleteObject(d[i][j]);
		}
		for(i=0;i<10;i++){
			for(j=0;j<20;j++)
				DeleteObject(e[i][j]);
		}
		DeleteObject(hrgn);
		DeleteDC(mdc);
		DeleteDC(bufdc);
		ReleaseDC(hWnd,hdc);
		PostQuitMessage(0);	
		break;
	default:							//其他消息
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
