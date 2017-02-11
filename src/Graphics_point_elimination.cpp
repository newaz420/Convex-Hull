#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<ctime>
#include<algorithm>
#include<vector>
#include<stack>
#include<graphics.h>
#include<queue>
#include<map>
#define FOR(i,k,n) for(int i=k;i<n;i++)
#define REP(i,k,n) for(int i=k;i<=n;i++)
#define PB push_back
#define EPS 1e-6
#define MP make_pair
using namespace std;
typedef double DD;
DD quardiliteral_area;
DD top_left_side;
DD top_right_side;
DD bottom_right_side;
DD bottom_left_side;
DD corner;
int N;
struct Point
{
    DD x,y;
};
struct Line_Info
{
    DD A,B,C,SQ;
};
stack<Point>ST;
vector<Point>V;
vector<Point>exist_point;
vector<Point>top_left_points;
vector<Point>top_right_points;
vector<Point>bottom_left_points;
vector<Point>bottom_right_points;
vector<Point>final_points;
map<pair<int,int>,bool>M;
Point Xmin,Ymin,Xmax,Ymax;
bool operator !=(Point  A,Point B)
{
    if(A.x!=B.x || A.y!=B.y) return true;
    return false;

}
ostream &operator <<(ostream &out,Point &P)
{
    out<<P.x<<" "<<P.y;
    return out;
}
istream &operator >>(istream &in,Point &P)
{
    in>>P.x>>P.y;
    return in;
}
DD dist(Point A,Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
DD cal_triangle_area(DD a,DD b,DD c)
{
    DD s=(a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

bool inside(Point A)
{
    //top_left_side
    DD up=dist(Ymax,A);
    DD down=dist(Ymin,A);
    DD left=dist(Xmin,A);
    DD right=dist(Xmax,A);
//cout<<up<<" "<<down<<" "<<left<<" "<<right<<endl;
    DD area1=cal_triangle_area(up,left,top_left_side);
    DD area2=cal_triangle_area(up,right,top_right_side);
    DD area3=cal_triangle_area(down,right,bottom_right_side);
    DD area4=cal_triangle_area(down,left,bottom_left_side);
    // cout<<(area1+area2+area3+area4)<<" got the area"<<endl;

    if((area1+area2+area3+area4)>(quardiliteral_area+EPS)) return false;
    return true;

}


DD cal_rectangle_area(Point Xmin,Point Ymax,Point Xmax,Point Ymin)
{

    top_left_side=dist(Xmin,Ymax);
    top_right_side=dist(Xmax,Ymax);
    bottom_right_side=dist(Xmax,Ymin);
    bottom_left_side=dist(Xmin,Ymin);
    corner=dist(Ymin,Ymax);

    DD area1=cal_triangle_area(top_left_side,bottom_left_side,corner);
    DD area2=cal_triangle_area(top_right_side,bottom_right_side,corner);

    return area1+area2;

}

DD dist_from_line_to_point(Point point,Line_Info line)
{
    return ((line.A*point.x+line.B*point.y+line.C)/line.SQ);
}
Line_Info make_straight_line(Point P,Point Q)
{
    Line_Info tmp;
    tmp.C=-(P.y-Q.y)*P.x+(P.x-Q.x)*P.y;
    tmp.A=(P.y-Q.y);
    tmp.B=(Q.x-P.x);
    tmp.SQ=sqrt(tmp.A*tmp.A+tmp.B*tmp.B);
    return tmp;
}
Point get_peak_point(vector<Point>top_points,Point A,Point B)
{
    Line_Info get_info=make_straight_line(A,B);
    DD mx=-(1<<31-1);
    Point top_p;
    FOR(i,0,top_points.size())
    {
        DD DIST=dist_from_line_to_point(top_points[i],get_info);
        if( DIST> mx+EPS)
        {
            top_p=top_points[i];
            mx=DIST;
        }

    }
    return top_p;
}
bool inside_triangle(Point P,Point X,Point Y,Point Z,DD side1,DD side2,DD side3,DD triangle_area)
{
    DD A=dist(X,P);
    DD B=dist(Y,P);
    DD C=dist(Z,P);
    DD area1=cal_triangle_area(A,C,side1);
    DD area2=cal_triangle_area(C,B,side2);
    DD area3=cal_triangle_area(A,B,side3);
    if((area1+area2+area3)>(triangle_area+EPS)) return false;
    return true;

}
int check(Point A,Point B,Point C)
{
    DD res=A.x*B.y-A.y*B.x+B.x*C.y-B.y*C.x+C.x*A.y-C.y*A.x;
    if(res<0)return -1;
    if(res>0)return 1;
    return 0;
}
bool compare(Point A,Point B)
{
    if(check(Ymin,A,B)==0)return dist(Ymin,A)<dist(Ymin,B);
    DD dx1=A.x-Ymin.x,dy1=A.y-Ymin.y;
    DD dx2=B.x-Ymin.x,dy2=B.y-Ymin.y;
    return dy1*dx2<dy2*dx1;
}
int main()
{
    int gdriver = EGA,gmode=EGAHI,errorcode;

    initgraph(&gdriver, &gmode, "");
    errorcode = graphresult();

    if (errorcode != grOk)     /* an error occurred */
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);               /* terminate with an error code */
    }

//int  maxcolor = getmaxcolor();

    cleardevice();
    setbkcolor(WHITE);
    cleardevice();
//setbkcolor(WHITE);

    Point temp,p;
    Line_Info get_info;
    int a=1,b=1;
    cin>>N;
    FOR(i,0,N)
    {
        // cin>>temp;
        temp.x=rand()%600;
        temp.y=rand()%300;
        //temp.y=rand()%1000000000;
        //  cout<<temp<<endl;
        if(M[MP(temp.x,temp.y)]==false)
        {
            V.PB(temp);
            M[MP(temp.x,temp.y)]=true;
        }

    }
    cout<<V.size()<<"hello";
    //cout<<"Hello"<<endl;
    clock_t t1,t2;
    t1=clock();
    Xmin.x=1000000001;
    Xmax.x=-1000000001;
    Ymin.y=1000000001;
    Ymax.y=-1000000001;

    FOR(i,0,N)
    {
        if(V[i].x<Xmin.x)
        {
            Xmin=V[i];
        }
        if(V[i].x>Xmax.x)
        {
            Xmax=V[i];
        }
        if(V[i].y<Ymin.y)
        {
            Ymin=V[i];
        }
        if(V[i].y>Ymax.y)
        {
            Ymax=V[i];
        }
        setcolor(7);
        setfillstyle(SOLID_FILL,GREEN);
        circle(V[i].x, V[i].y, 5);
        floodfill(V[i].x,V[i].y,7);
    }
    final_points.PB(Ymin);
    final_points.PB(Xmin);
    final_points.PB(Xmax);
    final_points.PB(Ymax);
    //cout<<"Hello"<<endl;
//cout<<Xmin<<endl<<Xmax<<endl<<Ymin<<endl<<Ymax<<endl;
    setcolor(1);
    line(Xmin.x,Xmin.y,Ymax.x,Ymax.y);
    //getch();
    setcolor(1);
    line(Ymax.x,Ymax.y,Xmax.x,Xmax.y);
    //getch();
    setcolor(1);
    line(Xmax.x,Xmax.y,Ymin.x,Ymin.y);
    //getch();
    setcolor(1);
    line(Ymin.x,Ymin.y,Xmin.x,Xmin.y);
    getch();
    quardiliteral_area=cal_rectangle_area(Xmin,Ymax,Xmax,Ymin);
    // cout<<quardiliteral_area<<endl;
    FOR(i,0,N)
    {
        if(Xmin!=V[i] && Xmax!=V[i] && Ymin!=V[i] && Xmax!=V[i])
        {
            if(!inside(V[i]))
            {
                exist_point.PB(V[i]);
            }

        }
    }
    //cout<<"Hello"<<endl;
    cout<<" existing points"<<endl;
    cout<<exist_point.size()<<endl;
    /* FOR(i,0,exist_point.size())
     {
         cout<<exist_point[i]<<endl;
     }*/
    FOR(i,0,exist_point.size())
    {
        if(exist_point[i].x<Ymax.x && exist_point[i].y>Xmin.y)
        {
            top_left_points.PB(exist_point[i]);
        }
        else if(exist_point[i].x>Ymax.x && exist_point[i].y>Xmax.y)
        {
            top_right_points.PB(exist_point[i]);
        }
        else if(exist_point[i].x>Ymin.x && exist_point[i].y<Xmax.y)
        {
            bottom_right_points.PB(exist_point[i]);
        }
        else if(exist_point[i].x<Ymin.x && exist_point[i].y<Xmin.y)
        {
            bottom_left_points.PB(exist_point[i]);
        }


    }
    //make straight line top_left_line
    Point top_left_p,top_right_p,bottom_right_p,bottom_left_p;
    //calculate another four boundry points
    if(!top_left_points.empty())
    {
        top_left_p=get_peak_point(top_left_points,Xmin,Ymax);
        final_points.PB(top_left_p);
        setcolor(RED);

        line(top_left_p.x,top_left_p.y,Xmin.x,Xmin.y);
        line(top_left_p.x,top_left_p.y,Ymax.x,Ymax.y);

        getch();
    }

    if(!top_right_points.empty())
    {
        top_right_p=get_peak_point(top_right_points,Ymax,Xmax);
        final_points.PB(top_right_p);
        setcolor(RED);

        line(top_right_p.x,top_right_p.y,Ymax.x,Ymax.y);
        line(top_right_p.x,top_right_p.y,Xmax.x,Xmax.y);

        getch();
    }
    if(!bottom_right_points.empty())
    {
        bottom_right_p=get_peak_point(bottom_right_points,Xmax,Ymin);
        final_points.PB(bottom_right_p);
        setcolor(RED);
        line(bottom_right_p.x,bottom_right_p.y,Ymin.x,Ymin.y);
        line(bottom_right_p.x,bottom_right_p.y,Xmax.x,Xmax.y);
        getch();
    }
    if(!bottom_left_points.empty())
    {
        bottom_left_p=get_peak_point(bottom_left_points,Ymin,Xmin);
        final_points.PB(bottom_left_p);
        setcolor(RED);
        line(bottom_left_p.x,bottom_left_p.y,Ymin.x,Ymin.y);
        line(bottom_left_p.x,bottom_left_p.y,Xmin.x,Xmin.y);
        getch();

    }




    //cout<<"peak points"<<endl;
    /*
        cout<<top_left_p<<endl;
        cout<<top_right_p<<endl;
        cout<<bottom_right_p<<endl;
        cout<<bottom_left_p<<endl;
    //top left*/
    DD side1=dist(Xmin,top_left_p);
    DD side2=dist(Ymax,top_left_p);
    DD tri_area=cal_triangle_area(side1,side2,top_left_side);
    FOR(i,0,top_left_points.size())
    {
        if(!inside_triangle(top_left_points[i],Xmin,Ymax,top_left_p,side1,side2,top_left_side,tri_area))
        {
            final_points.PB(top_left_points[i]);
        }

    }

//top right
    side1=dist(Xmax,top_right_p);
    side2=dist(Ymax,top_right_p);
    tri_area=cal_triangle_area(side1,side2,top_right_side);
    FOR(i,0,top_right_points.size())
    {
        if(!inside_triangle(top_right_points[i],Xmax,Ymax,top_right_p,side1,side2,top_right_side,tri_area))
        {
            final_points.PB(top_right_points[i]);
        }

    }

// bottom right
    side1=dist(Xmax,bottom_right_p);
    side2=dist(Ymin,bottom_right_p);
    tri_area=cal_triangle_area(side1,side2,bottom_right_side);
    FOR(i,0,bottom_right_points.size())
    {
        if(!inside_triangle(bottom_right_points[i],Xmax,Ymin,bottom_right_p,side1,side2,bottom_right_side,tri_area))
        {
            final_points.PB(bottom_right_points[i]);
        }

    }

//bottom left
    side1=dist(Xmin,bottom_left_p);
    side2=dist(Ymin,bottom_left_p);
    tri_area=cal_triangle_area(side1,side2,bottom_left_side);
    FOR(i,0,bottom_left_points.size())
    {
        if(!inside_triangle(bottom_left_points[i],Xmin,Ymin,bottom_left_p,side1,side2,bottom_left_side,tri_area))
        {
            final_points.PB(bottom_left_points[i]);
        }

    }
    //cout<<" final points "<<endl;
    //cout<<final_points.size()<<endl;
//FOR(i,0,final_points.size())cout<<final_points[i]<<endl;
    sort(++final_points.begin(),final_points.end(),compare);
//FOR(i,0,final_points.size())cout<<final_points[i]<<endl;
    Point First,Mid;
    ST.push(final_points[0]);
    ST.push(final_points[1]);
    N=final_points.size();
    FOR(i,2,N)
    {
        while(ST.size()>=2)
        {
            Mid=ST.top();
            ST.pop();
            First=ST.top();
            if(check(First,Mid,final_points[i])>=0)
            {
                ST.push(Mid);
                ST.push(final_points[i]);
                break;
            }
        }
    }
    int siz=ST.size();
    cout<<"Stack size "<<ST.size()<<endl;
    Point q,prothom;
    prothom=ST.top();
    while(!ST.empty())
    {
        p=ST.top();
        cout<<p<<endl;
        ST.pop();
        if(!ST.empty())
        {
            q=ST.top();
            setcolor(0);
            line(p.x,p.y,q.x,q.y);
            getch();
        }
    }
    if(siz&1)
    {
        setcolor(RED);
        line(prothom.x,prothom.y,p.x,p.y);
        getch();
    }
    else
    {
        setcolor(RED);
        line((prothom.x),(prothom.y),q.x,q.y);
        getch();
    }
    /*
      t2=clock();
      DD tm=(DD)t2-(DD)t1;
      cout<<tm/CLOCKS_PER_SEC<<endl;
      system("pause");
      */
    getch();
    closegraph();
    return 0;
}
/*
31
-3 16
11 3
-2 -12
-13 -1
8 13
7 -10
-9 -11
-12 10
2 2
8 2
2 10
1 8
6 2
6 6
4 -3
1 1
6 -2
-10 -1
-6 -3
-5 -5
-3 -8
-1 4
-3 9
-5 3
-7 6
-7 7
-11 4
-11 7
-9 8
-7 10
-10 12
*/
