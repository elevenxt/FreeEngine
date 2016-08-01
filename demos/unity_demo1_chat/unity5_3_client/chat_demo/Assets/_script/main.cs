using UnityEngine;
using System.Collections;
using System.IO;
using FreeEngineMsg;
using System;
using System.Text;

public class main : MonoBehaviour {
    public string ip = "127.0.0.1";
    public string port = "10101";
    public string ID = "user1";
    private string message = "";
    private string sendMsg = "";
    

    private socketClient _socket;

    void OnGUI()
    {
        ip = GUI.TextField(new Rect(10, 10, 100, 20), ip);
        port = GUI.TextField(new Rect(120, 10, 80, 20), port);
        message = GUI.TextArea(new Rect(10, 40, 300, 200), message);
        sendMsg = GUI.TextField(new Rect(10, 250, 210, 20), sendMsg);
        GUI.Label(new Rect(10, 280, 50, 20), "ID:");
        ID = GUI.TextField(new Rect(70, 280, 100, 20), ID);

        if (GUI.Button(new Rect(220, 10, 80, 20), "Connect"))
        {
            if (_socket == null || !_socket.isActive || !_socket.ip.Equals(ip) || !_socket.port.Equals(port))
            {
                _socket = new socketClient();
                _socket.Connect(ip, port);
                _socket.SetMessageListener(MessageListener);
            }            
        };
        if (GUI.Button(new Rect(230, 250, 80, 20), "Send"))
        {
            if (_socket == null || !_socket.isActive)
                return;

            FEMsg msg = new FEMsg();
            msg.msgtype = FEMsg.MSG_Type.Talk;
            msg.talk = new FEMsg_Talk();
            msg.talk.sender = ID;
            msg.talk.content = sendMsg;
            sendMsg = "";            

            msgSerializer se = new msgSerializer();
            MemoryStream protoStream = new MemoryStream();
            se.Serialize(protoStream, msg);
            byte[] data = protoStream.ToArray();

            //与freeEngine服务端通讯需要额外加2个字节，字节内容是包长度
            byte[] sendData = new byte[data.Length + 2];
            sendData[0] = (byte)(0xff & (data.Length + 2));
            sendData[1] = (byte)((0xff00 & (data.Length + 2)) >> 8);
            Buffer.BlockCopy(data, 0, sendData, 2, data.Length);

            _socket.SendMessage(sendData);
        };
    }

    void MessageListener(byte[] datas,int len)
    {
        msgSerializer se = new msgSerializer();
        //前2个字节是包长度信息，这里不做半包多包处理，忽略掉
        MemoryStream protoStream = new MemoryStream(datas,2,len-2);
        FEMsg msg = se.Deserialize(protoStream, null, typeof(FEMsg)) as FEMsg;

        switch (msg.msgtype)
        { 
            case FEMsg.MSG_Type.Info:
                message += string.Format("服务器版本：{0}\n", msg.gameInfo.version);
                break;
            case FEMsg.MSG_Type.Talk:
                message += string.Format("{0} : {1}\n",msg.talk.sender,msg.talk.content);
                break;
        }
    }

    void OnApplicationQuit()
    {
        if (_socket != null)
            _socket.DisConnect();
    }
}
