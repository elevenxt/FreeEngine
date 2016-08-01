using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System;

public class socketClient
{
    private TcpClient _client;
    private byte[] _data = new byte[4096];
    private Action<byte[], int> _callback;

    public string ip;
    public string port;
    public bool isActive { get { return _client != null && _client.Connected; } }
    

    public void Connect(string ip, string port)
    {
        this.ip = ip;
        this.port = port;
        _client = new TcpClient();
        _client.Connect(ip, int.Parse(port));
        _client.GetStream().BeginRead(_data, 0, _data.Length, ReceiveMessage, null);
    }

    public void DisConnect()
    {
        if (isActive)
            _client.Close();
    }

    public void SetMessageListener(Action<byte[],int> callback)
    {
        _callback = callback;
    }

    public void SendMessage(byte[] data)
    {
        if (!isActive)
            return;

        try
        {
            NetworkStream ns = _client.GetStream();
            ns.Write(data, 0, data.Length);
            ns.Flush();
        }
        catch (Exception ex)
        {
            Debug.LogError(ex.ToString());
        }
    }
    private void ReceiveMessage(IAsyncResult ar)
    {
        if (!isActive)
            return;

        try
        {
            int bytesRead;
            bytesRead = this._client.GetStream().EndRead(ar);
            if (bytesRead < 1)
            {
                return;
            }
            else
            {
                if (_callback != null)
                    _callback(_data,bytesRead);
            }
            this._client.GetStream().BeginRead(_data, 0, _data.Length, ReceiveMessage, null);
        }
        catch (Exception ex)
        {
            Debug.LogError(ex.ToString());
        }
    }

}
