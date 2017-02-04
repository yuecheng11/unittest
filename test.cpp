#include <iostream>

#include <string.h>

#include <string>

 using namespace std;

// 重定义数据类型

typedef unsigned char       UINT8;

typedef unsigned short int    UINT16;

typedef unsigned int        UINT32;

typedef signed   int        INT32;

// 消息头结构

typedef struct

{

    UINT16  iReserve1;

    UINT16  iReserve2;

    UINT16  iReserve3;

    UINT16  iReserve4;

}MsgHead_T;

 

// 消息结构体(包含消息头和消息体)

typedef struct

{

    MsgHead_T   MsgHead;                // 消息头

    UINT32      iOperType;      // 操作类型, 操作类型只能为1或2

    string       szUserNumber;         // 用户号码

    string       szOperTime;      // 操作时间, 格式为: yyyymmdd

    UINT32       iReserve1;                // 保留字段1

    string        szReserve2;           // 保留字段2

}UserReqMsg_T;

 

// 函数声明

INT32 ProcUserReqMsg(UserReqMsg_T *ptUserReqMsg);

INT32 main()

{

    UINT32  iRetVal          = 0;

    UINT32 iOperType        = 0;        // 操作类型

    string  szUserNumber;      // 用户号码

    string  szOperTime;    // 操作时间, 格式为: yyyymmdd

 

    UserReqMsg_T tUserReqMsg = {0};     // 请求消息

 

    // 对消息头部进行赋值

    tUserReqMsg.MsgHead.iReserve1 = 1;

    tUserReqMsg.MsgHead.iReserve2 = 2;

    tUserReqMsg.MsgHead.iReserve3 = 3;

    tUserReqMsg.MsgHead.iReserve4 = 4;

 

    // 读入具体消息字段的值

	char ch;
	cout<<"test begin y/n"<<endl;
	cin >> ch;
    while(ch == 'y')
    {

	    cout<<"input operator type "<<endl;

	    cin>>iOperType;

	    cout<<"input user number "<<endl;

	    cin>>szUserNumber;

	    cout<<"input time "<<endl;

	    cin>>szOperTime;

	 

	    // 对具体消息字段进行赋值(保留字段可不赋值)

	    tUserReqMsg.iOperType = iOperType;
		tUserReqMsg.szUserNumber = szUserNumber;
		tUserReqMsg.szOperTime = szOperTime;

	    // 对消息体的字段进行异常判断

	    iRetVal = ProcUserReqMsg(&tUserReqMsg);  // 注意: 传递参数的时候要加上&

	    if (iRetVal == 0)      // 函数执行正确

	    {

	        // 打印消息字段内容

	        cout<<"The user request message is: iOperType = "<<tUserReqMsg.iOperType<<",szUserNumber = " 
	        	<< tUserReqMsg.szUserNumber<<", szOperTime = %s."<< tUserReqMsg.szOperTime<<endl;

	        //return 0;

	    }

	    else         // 打印异常消息

	    {

	        cout<<"Some content of the user request message is wrong, please check again!"<<endl;

	       // return -1;

	    }

		cout<<"dou you want test again,y/n"<<endl;
		cin>>ch;
    }

	return 0;
}


INT32 ProcUserReqMsg(UserReqMsg_T *ptUserReqMsg)

{

    INT32  iRetValue      = 0;

 

    // 对输入参数进行异常判断

    if (ptUserReqMsg == NULL)

    {

        cout<<"ProcUserReqMsg(...): input parameter(ptUserReqMsg) is NULL."<<endl;
 

        return -1;

    }

 

    // 对消息体字段进行异常判断

    if ((ptUserReqMsg->iOperType != 1) && (ptUserReqMsg->iOperType != 2))    // 操作类型只能为1或2, 其它为数据异常

    {

        cout<<"ProcUserReqMsg(...): the iOperType is wrong, iOperType = "<< ptUserReqMsg->iOperType<<endl;

 

        return -2;

    }

   

    if (ptUserReqMsg->szUserNumber.length() != 8) // 用户号码异常, 长度8位才正确

    {

        cout<<"ProcUserReqMsg(...): the szUserNumber is wrong."<<endl;

 

        return -3;

    }

 

    if (ptUserReqMsg->szOperTime.length() != 8)  // 操作时间异常, 长度8位才正确

    {

        cout<<"ProcUserReqMsg(...): the szOperTime is wrong."<<endl;

       

        return -4;

    }

 

    return 0;

}
