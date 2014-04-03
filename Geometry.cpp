#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <cassert>
using namespace std;
ifstream fin("fence4.in");
ofstream fout("fence4.out");
namespace kingo
{
    class Vector;
    class Line;
    class LineSeg;

    bool isEqual(double v1,double v2)
    {
        return v1-v2 > -1e-8 && v1-v2 < 1e-8;
    }
    double abs(double value)
    {
        if(value<0) return -value;
        else return value;
    }

    class Vector
    {
    private:
    public:
        double x,y,z;
        Vector(){}
        Vector(double x,double y,double z):x(x),y(y),z(z) { }
        Vector(double x,double y):x(x),y(y),z(0) { }
        Vector operator * (const Vector &vector) const
        {
            return this->crossProduct(vector);
        }
        Vector crossProduct(const Vector &vector) const
        {
            Vector result;
            result.x = this->y*vector.z-this->z*vector.y;
            result.y = this->z*vector.x-this->x*vector.z;
            result.z = this->x*vector.y-this->y*vector.x;
            return result;
        }
        double dotProduct(const Vector &vector) const
        {
            return this->x*vector.x+this->y*vector.y+this->z*vector.z;
        }
        bool operator == (const Vector &vector)const
        {
            return isEqual(x,vector.x)&&isEqual(y,vector.y)&&isEqual(z,vector.z);
        }
        double length()
        {
            return sqrt(x*x+y*y+z*z);
        }
    };

    class Point
    {
    private:
    public:
        double x,y,z;
        Point(double x,double y,double z);
        Point(double x,double y);
        Point();
        double distanceTo(const Point& point) const;
        double distanceTo(const Line& line) const;
        int sideTo(const Line& line) const;
        bool isOn(const LineSeg& ls) const;
        bool isIn(const LineSeg& ls) const;
        bool operator == (const Point &point)const;
        Vector operator - (const Point &point) const;
    };

    class Line
    {
    public:
        Point p1,p2;
        Line(Point p1,Point p2);
        bool isCoplanar(const Line & line)const;
        bool isIntersectWith(const Line &line) const;
        bool isParallelWith(const Line &line) const;
        bool operator == (const Line &line) const;
        Point getIntersect(const Line & line) const;
    private:
        bool isSameDirect(const Line &line)const;
    };

    class LineSeg
    {
    public:
        Point p1,p2;
        LineSeg(Point p1,Point p2);
        Line toLine()const;
        double length()const;
        bool operator == (const LineSeg &ls)const;
        bool isIntersectWith(const Line &line) const;
        bool isIntersectWith(const LineSeg &lineSeg) const;
        bool isConnectWith(const LineSeg &lineSeg) const;
        bool isStrictIntersectWith(const LineSeg &lineSeg) const;
    };



    class Ray
    {
    public:
        Ray(Point start,Point toPoint);
        Ray(Point start,Vector direct);
        Point startPoint;
        Vector direct;
    };
    //Point
    Point::Point(double x,double y,double z):x(x),y(y),z(z) { }
    Point::Point(double x,double y):x(x),y(y),z(0) { }
    Point::Point():x(0),y(0),z(0){};
    double Point::distanceTo(const Point& point) const
    {
        double dx = this->x - point.x;
        double dy = this->y - point.y;
        double dz = this->z - point.z;
        return sqrt(dx*dx+dy*dy+dz*dz);
    }
    bool Point::operator == (const Point &point)const
    {
        return isEqual(x,point.x)&&isEqual(y,point.y)&&isEqual(z,point.z);
    }
    Vector Point::operator - (const Point &point) const
    {
        return Vector(x-point.x, y-point.y, z-point.z);
    }
    double Point::distanceTo(const Line& line) const
    {
        Vector pa = (*this) - line.p1;
        Vector ba = line.p2 - line.p1;
        Vector cross = pa.crossProduct(ba);
        double lenCross = cross.length();
        double lenBA = ba.length();
        assert(!isEqual(lenBA,0));
        return lenCross/lenBA;
    }
    int Point::sideTo(const Line& line) const
    {
        assert(isEqual(z,0));    
        assert(isEqual(line.p1.z,0));    
        assert(isEqual(line.p2.z,0));    
        Vector pa = (*this) - line.p1;
        Vector ba = line.p2 - line.p1;
        Vector cross = pa.crossProduct(ba);
        if(isEqual(cross.z,0)) return 0;
        else return cross.z > 0?1:-1;
    }
    bool Point::isOn(const LineSeg& ls) const
    {
        if(!isEqual(distanceTo(ls.toLine()),0)) return false;
        return isEqual(ls.length(),this->distanceTo(ls.p1)+this->distanceTo(ls.p2));
    }
    bool Point::isIn(const LineSeg &ls) const
    {
        if(!isEqual(distanceTo(ls.toLine()),0)) return false;
        double d1 = this->distanceTo(ls.p1);
        double d2 = this->distanceTo(ls.p2);
        return isEqual(d1+d2,ls.length())&&!isEqual(d1,0)&&!isEqual(d2,0);
    }

    //Line
    Line::Line(Point p1,Point p2):p1(p1),p2(p2) { }
    bool Line::isCoplanar(const Line & line)const
    {
        if(*this == line) return true;
        Vector thisVector = p2-p1;
        Vector interVector1 = line.p1 - p1;
        Vector interVector2 = line.p2 - p1;
        Vector cross = thisVector * interVector1;
        return isEqual(interVector2.dotProduct(cross),0);
    }
    bool Line::isIntersectWith(const Line & line)const
    {
        if(!isCoplanar(line)) return false;
        return !isSameDirect(line)||*this==line;
    }
    bool Line::isParallelWith(const Line &line) const
    {
        return isSameDirect(line) && !(*this==line);
    }
    bool Line::isSameDirect(const Line & line)const
    {
        Vector vThis = p1-p2;
        Vector vLine = line.p1 - line.p2;
        return isEqual(vThis.crossProduct(vLine).length(),0);
    }
    bool Line::operator == (const Line & line)const
    {
        return this->isSameDirect(line) && isEqual(p1.distanceTo(line),0);
    }
    Point Line::getIntersect(const Line & line) const
    {
        double xa = p1.x, ya = p1.y, xb = p2.x, yb = p2.y;
        double xc = line.p1.x, yc = line.p1.y, xd = line.p2.x, yd = line.p2.y;
        // xa+i(xb-xa) = xc+j(xd-xc)
        // ya+i(yb-ya) = yc+j(yd-yc)
        double dx1 = xb-xa,dy1=yb-ya,dx2 = xd-xc,dy2 = yd-yc;
        //xa*dy2 + i*dx1*dy2 = xc*dy2+j*dx2*dy2
        //ya*dx2 + i*dy1*dx2 = yc*dx2+j*dy2*dx2
        double pi = dx1*dy2-dy1*dx2;
        double vi = xc*dy2-yc*dx2-xa*dy2+ya*dx2;
        assert(!isEqual(pi,0));
        double i = vi/pi;
        return Point(xa+i*(xb-xa),ya+i*(yb-ya));
    }

    //LineSeg
    LineSeg::LineSeg(Point p1,Point p2):p1(p1),p2(p2) { }
    Line LineSeg::toLine()const
    {
        return Line(p1,p2);
    }
    double LineSeg::length()const
    {
        return p1.distanceTo(p2);
    }
    bool LineSeg::isIntersectWith(const Line &line) const
    {
        assert(isEqual(p1.z,0));
        assert(isEqual(p2.z,0));
        assert(isEqual(line.p1.z,0));
        assert(isEqual(line.p2.z,0));
        int side1 = p1.sideTo(line);
        int side2 = p2.sideTo(line);
        return side1==0||side2==0||side1!=side2;
    }
    bool LineSeg::isIntersectWith(const LineSeg &lineSeg) const
    {
        assert(isEqual(p1.z,0));
        assert(isEqual(p2.z,0));
        assert(isEqual(lineSeg.p1.z,0));
        assert(isEqual(lineSeg.p2.z,0));
        Line thisLine = this->toLine();
        Line otherLine = lineSeg.toLine();
        if(thisLine == otherLine)
        {
            return p1.isOn(lineSeg)||p2.isOn(lineSeg)||lineSeg.p1.isOn(*this)||lineSeg.p2.isOn(*this);
        }
        else
        {
            int sideThis1 = p1.sideTo(otherLine);
            int sideThis2 = p2.sideTo(otherLine);
            int sideOther1 = lineSeg.p1.sideTo(thisLine);
            int sideOther2 = lineSeg.p2.sideTo(thisLine);
            return (sideThis1*sideThis2==0||sideThis1 * sideThis2==-1)
                && (sideOther1*sideOther2==0 || sideOther1* sideOther2 == -1);
        }
    }
    bool LineSeg::isStrictIntersectWith(const LineSeg &lineSeg) const
    {
        assert(isEqual(p1.z,0));
        assert(isEqual(p2.z,0));
        assert(isEqual(lineSeg.p1.z,0));
        assert(isEqual(lineSeg.p2.z,0));
        if(*this == lineSeg) return true;
        Line thisLine = this->toLine();
        Line otherLine = lineSeg.toLine();
        if(thisLine == otherLine)
        {
            return p1.isIn(lineSeg)||p2.isIn(lineSeg)||lineSeg.p1.isIn(*this)||lineSeg.p2.isIn(*this);
        }
        else
        {
            int sideThis1 = p1.sideTo(otherLine);
            int sideThis2 = p2.sideTo(otherLine);
            int sideOther1 = lineSeg.p1.sideTo(thisLine);
            int sideOther2 = lineSeg.p2.sideTo(thisLine);
            return (sideThis1 * sideThis2==-1)
                && (sideOther1* sideOther2 == -1);
        }
    }
    bool LineSeg::isConnectWith(const LineSeg &lineSeg) const
    {
        if(p1 == lineSeg.p1||p1 == lineSeg.p1 || p2 == lineSeg.p1 || p2 == lineSeg.p2)
        {
            Line thisLine = this->toLine();
            Line otherLine = lineSeg.toLine();
            if(thisLine == otherLine)
            {
                return !p1.isIn(lineSeg) && !p2.isIn(lineSeg)
                    && !lineSeg.p1.isIn(*this) && !lineSeg.p2.isIn(*this);
            }
            else
            {
                return true;
            }
        }
        else return false;
    }
    bool LineSeg::operator == (const LineSeg &ls)const
    {
        return (p1==ls.p1 && p2==ls.p2)||(p1==ls.p2 && p2==ls.p1);
    }

    //Ray
    Ray::Ray(Point start,Point toPoint):startPoint(start)
    {
        assert(!(start == toPoint));
        direct = toPoint-start;
    }
    Ray::Ray(Point start,Vector direct):startPoint(start),direct(direct)
    {
        assert(!isEqual(direct.length(),0));
    }
    void testGeometry()
    {
        {
            Point pa(3,4,5),pb(5,4,5);
            assert(isEqual(pa.distanceTo(pb),2));
            Vector va(1,1,1),vb(1,-1,1);
            assert(isEqual(va.dotProduct(vb),1));
            assert(va.crossProduct(vb)==Vector(2,0,-2));
            Line xaxis(Point(1,0,0),Point(0,0,0));
            Line pxaxis(Point(1,1,0),Point(0,1,0));
            Line yaxis(Point(0,1,0),Point(0,0,0));
            Line yaxisElse(Point(2,1,2),Point(2,0,2));
            Line xaxisElse(Point(-10,0,0),Point(0,0,0));
            assert(isEqual(pa.distanceTo(xaxis),sqrt(41)));
            assert(xaxis == xaxisElse);
            assert(!(xaxis == yaxis));
            assert(xaxis.isCoplanar(yaxis));
            assert(!xaxis.isCoplanar(yaxisElse));
            assert(xaxis.isIntersectWith(yaxis));
            assert(!xaxis.isIntersectWith(yaxisElse));
            assert(xaxis.isIntersectWith(xaxisElse));
            assert(!xaxis.isParallelWith(xaxisElse));
            assert(!xaxis.isParallelWith(yaxis));
            assert(xaxis.isParallelWith(pxaxis));
        }
        {
            LineSeg ls1(Point(0,0),Point(0,10));
            LineSeg ls2(Point(0,1),Point(0,11));
            LineSeg ls3(Point(10,1),Point(-10,1));
            LineSeg ls4(Point(10,1),Point(1,1));
            assert(ls1.isIntersectWith(ls2));
            assert(ls1.isIntersectWith(ls3));
            assert(!ls1.isIntersectWith(ls4));
        }
        {
            Line line1(Point(1,0),Point(0,0));
            Line line2(Point(0,1),Point(0,0));
            Line line3(Point(0,-1),Point(1,1));
            assert(line1.getIntersect(line2) == Point(0,0));
            assert(line1.getIntersect(line3) == Point(0.5,0));
        }
    }
}
using namespace kingo;
bool inTri(Point pO,Point pA,Point pB,Point pC)
{
    int sideA = pA.sideTo(Line(pB,pC));
    int sideB = pB.sideTo(Line(pA,pC));
    int sideC = pC.sideTo(Line(pB,pA));
    int sideOA = pO.sideTo(Line(pB,pC));
    int sideOB = pO.sideTo(Line(pA,pC));
    int sideOC = pO.sideTo(Line(pB,pA));
    return sideA==sideOA&&sideB==sideOB&&sideC==sideOC;
}
bool csort(const pair<int,int> &v1, const pair<int,int> &v2)
{
    return v1.second < v2.second || (v1.second==v2.second && v1.first<v2.first);
}
int main(int argv,char*argc[])
{
    int N;
    kingo::Point ob;
    kingo::Point fence[201];
    vector<kingo::LineSeg> lineSegs;
    fin >> N;
    fin >> ob.x >> ob.y;
    for(int i=0;i<N;++i)
    {
        fin >> fence[i].x >> fence[i].y;
    }
    fence[N] = fence[0];
    bool isOK = true;
    for(int i=0; i < N;++i)
    {
        lineSegs.push_back(kingo::LineSeg(fence[i],fence[i+1]));
    }
    //cout << fence[1].sideTo(lineSegs[1].toLine()) << endl;
    //return 0;
    for(int i=0; i < N;++i)
    {
        for(int j=i+1;j<N;++j)
        {
            if(lineSegs[i].isStrictIntersectWith(lineSegs[j]))
            {
                isOK = false;
                break;
            }
        }
        if(!isOK) break;
    }
    if(!isOK)
    {
        fout << "NOFENCE" << '\n';
        return 0;
    }
    bool isA;
    bool isB;
    bool isVisual;
    int oldSide,side1,side2;
    vector<pair<int,int> >res;
    for(int i=0;i<N;++i)
    {
        kingo::Point pA = lineSegs[i].p1;
        kingo::Point pB = lineSegs[i].p2;
        kingo::LineSeg lsA(ob,pA);
        kingo::LineSeg lsB(ob,pB);
        if(lsA.toLine() == lsB.toLine()) continue;
        kingo::Line lineAB = lineSegs[i].toLine();
        isVisual = true;
        for(int k=0;k<N;++k)
        {
            int j = (i+1+k)%N;
            if(i==j)continue;
            isA = lsA.isIntersectWith(lineSegs[j]);
            isB = lsB.isIntersectWith(lineSegs[j]);
            if(isA&&isB)
            {
                isVisual = false;
            }
            else if(isA)
            {
                oldSide = pB.sideTo(lsA.toLine());
                side1 = lineSegs[j].p1.sideTo(lsA.toLine());
                side2 = lineSegs[j].p2.sideTo(lsA.toLine());
                if(inTri(lineSegs[j].p1,pA,pB,ob))
                {
                    pA = lineAB.getIntersect(kingo::Line(ob,lineSegs[j].p1));
                    lsA = kingo::LineSeg(ob,pA);
                }
                else if(inTri(lineSegs[j].p2,pA,pB,ob))
                {
                    pA = lineAB.getIntersect(kingo::Line(ob,lineSegs[j].p2));
                    lsA = kingo::LineSeg(ob,pA);
                    
                }
            }
            else if(isB)
            {
                oldSide = pA.sideTo(lsB.toLine());
                side1 = lineSegs[j].p1.sideTo(lsB.toLine());
                side2 = lineSegs[j].p2.sideTo(lsB.toLine());
                if(inTri(lineSegs[j].p1,pA,pB,ob))
                {
                    pB = lineAB.getIntersect(kingo::Line(ob,lineSegs[j].p1));
                    lsB = kingo::LineSeg(ob,pB);
                }
                else if(inTri(lineSegs[j].p2,pA,pB,ob))
                {
                    pB = lineAB.getIntersect(kingo::Line(ob,lineSegs[j].p2));
                    lsB = kingo::LineSeg(ob,pB);
                    
                }
            }
        }
        if(isVisual && !isEqual(pA.distanceTo(pB),0))
        {
            if(i==19)
            {
                cout << lineSegs[i].p1.x << lineSegs[i].p1.y << endl;
                cout << pA.x << pA.y << endl;
                cout << pA.distanceTo(pB) << endl;
            }
            if(i+1==N) res.push_back(make_pair(0,i));
            else res.push_back(make_pair(i,i+1));
        }
    }
    sort(res.begin(),res.end(),csort);
    fout << res.size() << '\n';
    for(int i=0;i<res.size();++i)
    {
        fout << fence[res[i].first]. x << ' ' << fence[res[i].first].y
                << ' ' << fence[res[i].second].x << ' ' << fence[res[i].second].y << endl;
    }
    kingo::testGeometry();
    return 0;
}
