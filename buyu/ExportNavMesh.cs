/************************************************
 * 文件名:
 * 描述:网格导航
 * 创建人:tinyult
 * 创建日期：20160926
 * http://blog.csdn.net/huutu/article/details/52672505
 * ************************************************/

using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using UnityEngine.SceneManagement;
using System.Collections.Generic;


public class Nears
{
    public int Index;//网格索引
    public float Distance;//与相邻网格的距离
    public int[] PointIndex = new int[2];//相邻的点索引
    public int NotNearPointIndex = -1;//不相邻的点
}
public class Cell
{
    public int index = -1;//网格索引
    public Vector3[] v = new Vector3[3];//网格点
    public Vector3 MidPos = new Vector3();//中心点
    public List<Nears> nears = new List<Nears>();//相邻网格
    public float costToSource = 0;//与源的距离
    public float fValue = 0;//消耗值
    public Cell parent = null;//父节点
    public Cell child = null;//子节点
    public float MaxX = 0;//最大x值
    public float MaxY = 0;//最大y值
    public float MinX = 0;//最小x值
    public float MinY = 0;//最小y值
}
public class ExportNavMesh
{
    static void InsertNears(Cell a, Cell b, int index, List<int> l)
    {
        foreach(var n in a.nears)
        {
            if(n.Index == index)
            {
                return;
            }
        }
        var c = new Nears { Index = index, Distance = Vector3.Distance(a.MidPos, b.MidPos) };
        c.PointIndex[0] = l[0];
        c.PointIndex[1] = l[1];
        c.NotNearPointIndex = l[2];
        a.nears.Add(c);
    }
    static bool IsNearCell(Cell a, Cell b, List<int> l)
    {
        int samePointCount = 0;
        for(int i = 0; i < 3; i++)
        {
            if(i ==2 && samePointCount == 0)
            {
                return false;
            }
            Vector3 c1 = a.v[i];
            for(int j = 0; j < 3; j++)
            {
                Vector3 c2 = b.v[j];

                if(c1 == c2)
                {
                    l.Add(j);
                    samePointCount++;
                    if(samePointCount == 2)
                    {
                        for(int k = 0; k < 3; k++)
                        {
                            Vector3 c3 = b.v[k];
                            if(c3 != b.v[l[0]] && c3 != b.v[l[1]])
                            {
                                l.Add(k);
                            }
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }
    static bool SameSide(Vector3 A, Vector3 B, Vector3 C, Vector3 P)
    {
        Vector3 BA = B - A;
        Vector3 CA = C - A;
        Vector3 PA = P - A;

        Vector3 v1 = Vector3.Cross(BA, CA); 
        Vector3 v2 = Vector3.Cross(BA, PA);//a × b = |a| |b| sin(θ) n

        // v1 and v2 should point to the same direction
        return Vector3.Dot(v1, v2) > 0;// v1.Dot(v2) >= 0;点乘的结果越大，表示两个向量越接近
    }

    static bool PointinTriangle(Vector3 A, Vector3 B, Vector3 C, Vector3 P)
    {
        return SameSide(A, B, C, P) &&
            SameSide(B, C, A, P) &&
            SameSide(C, A, B, P);
    }
    static float GetMaxX(Vector3 a, Vector3 b, Vector3 c)
    {
        return Mathf.Max( new float[3] { a.x, b.x, c.x });

    }
    static float GetMaxZ(Vector3 a, Vector3 b, Vector3 c)
    {
        return Mathf.Max(new float[3] { a.z, b.z, c.z });

    }
    static float GetMinX(Vector3 a, Vector3 b, Vector3 c)
    {
        return Mathf.Min(new float[3] { a.x, b.x, c.x });

    }
    static float GetMinZ(Vector3 a, Vector3 b, Vector3 c)
    {
        return Mathf.Min(new float[3] { a.z, b.z, c.z });

    }
    static float GetAreaSize(Vector3 a, Vector3 b, Vector3 c)
    {
        var S = 0.5f * (a.x * b.z + b.x * c.z + c.x * a.z - a.x * c.z - b.x * a.z - c.x * b.z);
        return S;
    }
    public static List<Cell> list;//= new List<Cell>();

    public static List<Cell> pathList;//= new List<Cell>();
    [MenuItem("NavMesh/StartFind")]
    static void Find()
    {
        pathList = new List<Cell>();
        Walk();
    }
    [MenuItem("NavMesh/Export")]
    static void Export()
    {
        Debug.Log("ExportNavMesh");

        UnityEngine.AI.NavMeshTriangulation tmpNavMeshTriangulation = UnityEngine.AI.NavMesh.CalculateTriangulation();

     
        list = new List<Cell>();
        
        //索引
        for (int i = 0; i < tmpNavMeshTriangulation.indices.Length;)
        {
            var cell = new Cell();
            cell.v[0] = tmpNavMeshTriangulation.vertices[tmpNavMeshTriangulation.indices[i]];
            cell.v[1] = tmpNavMeshTriangulation.vertices[tmpNavMeshTriangulation.indices[i+1]];
            cell.v[2] = tmpNavMeshTriangulation.vertices[tmpNavMeshTriangulation.indices[i+2]];
            cell.v[0].y = 0; 
            cell.v[1].y = 0; 
            cell.v[2].y = 0;
            cell.MidPos = (cell.v[0] + cell.v[1] + cell.v[2]) / 3;
            cell.MaxX = GetMaxX(cell.v[0], cell.v[1], cell.v[2]);
            cell.MaxY = GetMaxZ(cell.v[0], cell.v[1], cell.v[2]);
            cell.MinX = GetMinX(cell.v[0], cell.v[1], cell.v[2]);
            cell.MinY = GetMinZ(cell.v[0], cell.v[1], cell.v[2]);
            //cell.AreaSize = GetAreaSize(cell.v[0], cell.v[1], cell.v[2]);
            cell.index = list.Count;
            list.Add(cell);
            i = i + 3;
        }
        for(int i = 0; i < list.Count; i++)
        {
            var a = list[i];
            for(int j =0; j < list.Count; j++)
            {
                var b = list[j];
                if (a != b)
                {
                    List<int> l = new List<int>();
                    if(IsNearCell(a, b, l))
                    {
                        InsertNears(a, b, j, l);
                    }
                }
            }
        }

        Debug.Log("ExportNavMesh Success");

        
    }
    static List<Cell> openList = new List<Cell>();
    static List<Cell> closeList = new List<Cell>();
    static Cell GetMinPathFormOpenList()
    {
        if(openList.Count > 0)
        {
            Cell minC = openList[0];
            foreach(var c in openList)
            {
                if(c.fValue  < minC.fValue)
                {
                    minC = c;
                }
            }
            return minC;
        }

        return null;
    }
    static void RemoveObjFromOpenList(Cell cell)
    {
        if(cell == null)
        {
            return;
        }
        openList.Remove(cell);
    }
    static void  InspectTheAdjacentNodes(Cell cell, Cell adjacent,float distance, Vector3 endPos)
    {
        if(adjacent == null)
        {
            return;
        }
        adjacent.costToSource = cell.costToSource + distance;
        var G = adjacent.costToSource;
        var H = Vector3.Distance(endPos, adjacent.MidPos);
        adjacent.fValue = G + H;
        adjacent.parent = cell;
        
        cell.child = adjacent;

        closeList.Add(adjacent);
        openList.Add(adjacent);
    }
    static void BuildPath(Cell start_Cell, Vector3 start_Pos, Cell end_Cell, Vector3 end_Pos)
    {
        openList.Clear();
        closeList.Clear();

        end_Cell.fValue = 0;
        end_Cell.costToSource = 0;

        openList.Add(end_Cell);
        closeList.Add(end_Cell);

        Cell cell = null;
        while (true)
        {
            //得到离起始点最近的点(如果是第一次执行, 得到的是起点)
            cell = GetMinPathFormOpenList();
            if(cell == null)
            {
                //不到路径
                break;
            }
            //把计算过的点从开放列表中删除
            RemoveObjFromOpenList(cell);

            if(cell == start_Cell)
            {
                break;
            }

            for(int i = 0; i < cell.nears.Count; i++)
            {
                var c = list[cell.nears[i].Index];
                if (!closeList.Contains(c))
                {
                    var distance = cell.nears[i].Distance;
                    InspectTheAdjacentNodes(cell, c, distance, start_Pos);
                }
            }
        }

        Vector3 lastFirst = new Vector3();
        Vector3 lastSecond = new Vector3();
        //cell = end_Cell;
        while (cell != null)
        {
            //把路径点加入到路径列表中
            pathList.Add(cell);

            var parent = cell.parent;

            if (parent != null)
            {
                Vector3 V1;
                Vector3 V2 ;
                Vector3 V3;
                bool hasadd = false;
               // bool seconded = false;

                GetEqualPoint(cell, parent,out V1,out V2, out V3);
                if (firstPoints.Count == 0)
                {
                    firstPoints.Add(new NavPoint() { v = V1, cell = parent });
                    lastFirst = V1;
                    hasadd = true;
                }
                if (SecondPoints.Count == 0)
                {
                    SecondPoints.Add(new NavPoint() { v = V2, cell = parent });
                    lastSecond = V2;
                    hasadd = true;
                }

                if (!hasadd)
                {
                    if (V1 == lastFirst)
                    {
                        SecondPoints.Add(new NavPoint() { Index = SecondPoints.Count,  v = V2, cell = parent, ConnectIndex = firstPoints.Count - 1 });
                        firstPoints[firstPoints.Count - 1].cell = parent;
                        firstPoints[firstPoints.Count - 1].ConnectIndex = SecondPoints.Count - 1;
                        lastSecond = V2;
                        hasadd = true;
                    }
                    else if (V1 == lastSecond)
                    {
                        firstPoints.Add(new NavPoint() { Index = firstPoints.Count, v = V2, cell = parent, ConnectIndex = SecondPoints.Count - 1 });
                        SecondPoints[SecondPoints.Count - 1].cell = parent;
                        SecondPoints[SecondPoints.Count - 1].ConnectIndex = firstPoints.Count - 1;
                        lastFirst = V2;
                        hasadd = true;
                    }
                }

                if (!hasadd)
                {
                    if (V2 == lastFirst)
                    {
                        SecondPoints.Add(new NavPoint() { Index = SecondPoints.Count,  v = V1, cell = parent, ConnectIndex= SecondPoints.Count - 1 });
                        firstPoints[firstPoints.Count - 1].cell = parent;
                        firstPoints[firstPoints.Count - 1].ConnectIndex = SecondPoints.Count - 1;
                        lastSecond = V1;
                    }
                    else if (V2 == lastSecond)
                    {
                        firstPoints.Add(new NavPoint() { Index = firstPoints.Count, v = V1, cell = parent, ConnectIndex = SecondPoints.Count - 1 });
                        SecondPoints[SecondPoints.Count - 1].cell = parent;
                        SecondPoints[SecondPoints.Count - 1].ConnectIndex = firstPoints.Count - 1;
                        lastFirst = V1;
                    }
                }
            }

            cell = parent;
        }
    }
    public static void GetEqualPoint(Cell a, Cell b, out  Vector3 v1, out Vector3 v2, out Vector3 v3)
    {
        v1 = new Vector3();
        v2 = new Vector3();
        v3 = new Vector3();
        for(int i = 0; i < a.nears.Count; i++)
        {
            var n = a.nears[i];
            if(n.Index == b.index)
            {
                v1 = b.v[n.PointIndex[0]];
                v2 = b.v[n.PointIndex[1]];
                v3 = b.v[n.NotNearPointIndex];
            }
        }
    }
    public class NavPoint
    {
        public int Index;
        public Vector3 v;
        public Cell cell;
        public int ConnectIndex = -1;
    }
    public static List<NavPoint> firstPoints;
    public static List<NavPoint> SecondPoints;

    static void Walk()
    {
        firstPoints = new List<NavPoint>();
        SecondPoints = new List<NavPoint>();

        Vector3 startPos = new Vector3();
        startPos.x = 1.8f;
        startPos.z = 1.59f;

        Vector3 endPos = new Vector3();
        endPos.x = 8.79f;
        endPos.z = 5.29f;

        Cell startCell = null;
        Cell endCell = null;
         
        foreach (var cell in list)
        {
            if (startCell == null && PointinTriangle(cell.v[0], cell.v[1], cell.v[2], startPos ))
            {
                startCell = cell;
            }
            if (endCell == null && PointinTriangle(cell.v[0], cell.v[1], cell.v[2], endPos))
            {
                endCell = cell;
            }
            if(endCell != null && startCell != null)
            {
                break;
            }
        }
        if (endCell != null && startCell != null)
        {
            BuildPath(startCell, startPos, endCell, endPos);
            Debug.Log("Build Done");
            SetPath(startPos, endPos);
        }

    }
   public static List<Vector3> FinalPath;
    static void SetPath(Vector3 startPos, Vector3 endPos)
    {
        FinalPath = new List<Vector3>();

        FinalPath.Add(startPos);
        firstPoints.Add(new NavPoint() {v = endPos } );
        SecondPoints.Add(new NavPoint() { v = endPos });

        int firstI = 0;
        int secondI = 0;

        var firstStep = 0;
        var secondStep = 0;
        bool c1 = true;
        bool c2 = true;
        int bi1 = -1;
        int bi2 = -1;
 
        while (true)
        {
            if (firstI + firstStep + 1 >= firstPoints.Count )
            {
                c1 = false;
            }
            else
            {
                c1 = true;
            }
            if (secondI + secondStep + 1 >= SecondPoints.Count)
            {
                c2 = false;
            }
            else
            {
                c2 = true;
            }
     
            if(c1 && secondI < SecondPoints.Count)
            bi1 = WhichIsBetween(startPos, firstPoints[firstI].v, SecondPoints[secondI].v, firstPoints[firstI + firstStep + 1].v);
            if(c2 && firstI < firstPoints.Count)
            bi2 = WhichIsBetween(startPos, firstPoints[firstI].v, SecondPoints[secondI].v, SecondPoints[secondI + secondStep + 1].v);

            if (bi1 == 0)//s -- p_f -- f
            {
                if (c1)
                {
                    if (firstStep > 0)
                    {
                        firstStep++;
                    }
                    else
                    {
                        firstI++;
                    }
                }
            }
            else if (bi1 == 1)//s -- f -- p_f
            {
                if (c1)
                    firstStep++;
            }
            else if (bi1 == 2)//p_f -- s -- f， s为拐点
            {
                if(secondI <  SecondPoints.Count)
                {
                    startPos = SecondPoints[secondI].v;
                    FinalPath.Add(startPos);
                   
                    firstStep = 0;
                    secondStep = 0;


                   
                    firstI = SecondPoints[secondI].ConnectIndex;
                    if(firstI == -1)
                    {
                        firstI = firstPoints.Count;
                    }
                    secondI++;
                }
               
            }

            if (bi2 == 0)//f -- p_s -- s
            {
                if (c2)
                {
                    if (secondStep > 0)
                    {
                        secondStep++;
                    }
                    else
                    {
                        secondI++;
                    }
                }
            }
            else if (bi2 == 1)//s -- f -- p_s f为拐点
            {
                if(firstI < firstPoints.Count)
                {
                    startPos = firstPoints[firstI].v;
                    FinalPath.Add(startPos);
                    
                    firstStep = 0;
                    secondStep = 0;

                    //secondI = oldSecondIndex;
                    secondI = firstPoints[firstI].ConnectIndex;
                    if(secondI == -1)
                    {
                        secondI = SecondPoints.Count;
                    }
                    firstI++;
                }
               
            }
            else if (bi2 == 2)//p_s -- s -- f
            {
                if(c2)
                secondStep++;
            }
         

            if (c1 == false && c2 == false)
            {
                break;
            }

        }
        FinalPath.Add(endPos);


    }

    static bool MySameSide(Vector3 A, Vector3 B, Vector3 C, Vector3 P)
    {
        Vector3 AB = A-B;
        Vector3 AC = A-C;
        Vector3 AP = A-P;

        Vector3 v1 = Vector3.Cross(AB, AP);
        Vector3 v2 = Vector3.Cross(AC, AP);//a × b = |a| |b| sin(θ) n

        // v1 and v2 should point to the same direction
        return Vector3.Dot(v1, v2) < 0;// v1.Dot(v2) >= 0;点乘的结果越大，表示两个向量越接近
    }
    [MenuItem("NavMesh/test")]
    static void test()
    {
        Vector3 A = new Vector3() {x = 0, y = 0, z = 0 };
        Vector3 B = new Vector3() {x = 0, y = 1, z = 0 };
        Vector3 C = new Vector3() {x = 1, y = 0, z = 0 };
        Vector3 P = new Vector3() {x = 1, y = -1, z = 0 };
        var a = SameSide(A,B,C,P) && SameSide(A, C, B, P);
        Debug.Log(a);
    }
    static int WhichIsBetween(Vector3 O/*原点*/, Vector3 F/*first*/, Vector3 S/*second*/, Vector3 P)
    {
        if (IsBetween(O, F, S, P))
        {
            return 0;
        }
        else if(IsFirstBetween(O, F, S, P))
        {
            return 1;
        }
        else if(IsSecondBetween(O, F, S, P))
        {
            return 2;
        }else
        {
            var FN = (F - O).normalized;
            var PN = (P - O).normalized;
            var SN = (S - O).normalized;
            if(FN == PN)
            {
                return 1;
            }
            else if (SN == PN)
            {
                return 2;
            }
            return 1;
        }
    }
    static bool IsBetween(Vector3 O/*原点*/, Vector3 F/*first*/, Vector3 S/*second*/, Vector3 P)
    {
        return SameSide(O, F, S, P) && SameSide(O, S, F, P);
    }

    //是否是first在中间
    static bool IsFirstBetween(Vector3 O/*原点*/, Vector3 F/*first*/, Vector3 S/*second*/, Vector3 P)
    {
        if(IsBetween(O, S, P, F))
        {
            return true;
        }
        return false;
    }
    //是否是second在中间
    static bool IsSecondBetween(Vector3 O/*原点*/, Vector3 F/*first*/, Vector3 S/*second*/, Vector3 P)
    {
        if (IsBetween(O, F, P, S))
        {
            return true;
        }
        return false;
    }


}
