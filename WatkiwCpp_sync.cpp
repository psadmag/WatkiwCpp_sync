#include "pch.h"
using namespace System;
using namespace System::Threading;
using namespace System::Collections;


public ref class Prime {
public:
    static int prime = 0;
    static ArrayList^ tabPrime = gcnew ArrayList();
public:
    bool PrimeTest(int n) {
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        else {
            int d = 3;
            while (d <= Math::Sqrt(n)) {
                if (n % d == 0) return false;
                d += 2;
            }
        }
        return true;
    }
    int ArrayPrime(int max) {
        for (prime = 3; prime <= max; prime += 2) {
            if (this->PrimeTest(prime)) {
                tabPrime->Add(prime);
                //prime = i;
                Console::ForegroundColor = ConsoleColor::White;
                Console::Write(prime);
                Console::Write(",");
            }
        }
        return tabPrime->Count;
    }
};

public ref class ThreadPrime {

public: void ThreadProc() {
    Prime^ obj = gcnew Prime();
    int x= obj->ArrayPrime(10000);
    //for each (int i in Prime::tabPrime)
    //{
    //    Console::Write(i);
    //    Console::Write(",");
    //}
    }

public: void ThreadProcPrimeNumber() {
    Prime^ obj = gcnew Prime();
    Console::ForegroundColor = ConsoleColor::Red;
    Console::Write("...[");
    Prime::prime = 19;
    Console::Write(Prime::prime);
    Console::Write("]...");

}
};


public ref class MessageBuffer
{
    String^ messageText;
   
public:
  
    void SetMessage(String^ s)
    {
        /*7*/       Monitor::Enter(this);
        messageText = s;
        /*8*/       Monitor::Pulse(this);
        Console::WriteLine("Set new message {0}", messageText);
        Monitor::Exit(this);
    }

    void ProcessMessages()
    {
        /*9*/       Monitor::Enter(this);
        while (true)
        {
            try
            {
                /*10*/              Monitor::Wait(this);
            }
            catch (ThreadInterruptedException^ e)
            {
                Console::WriteLine("ProcessMessage interrupted");
                return;
            }

            Console::WriteLine("Processed new message {0}", messageText);
        }
        Monitor::Exit(this);
    }
};

public ref class CreateMessages
{
    MessageBuffer^ msg;
public:
    CreateMessages(MessageBuffer^ m)
    {
        msg = m;
    }

    void CreateMessagesEntryPoint()
    {
        for (int i = 1; i <= 5; ++i)
        {
            msg->SetMessage(String::Concat("M-", i.ToString()));
            Thread::Sleep(2000);
        }
        Console::WriteLine("CreateMessages thread terminating");
    }
};

public ref class ProcessMessages
{
    MessageBuffer^ msg;
public:
    ProcessMessages(MessageBuffer^ m)
    {
        msg = m;
    }

    void ProcessMessagesEntryPoint()
    {
        msg->ProcessMessages();
        Console::WriteLine("ProcessMessages thread terminating");
    }
};


int main()
{
    Prime ^obj = gcnew Prime();
    //bool p = obj->PrimeTest(19);
    //int x= obj->ArrayPrime(1000);
    //for each (int i in Prime::tabPrime)
    // {
    //    Console::Write(i);
    //    Console::Write(",");
    //}
    ThreadPrime^ pp1 = gcnew ThreadPrime();
    Thread^ pmt1 = gcnew Thread(gcnew ThreadStart(pp1,&ThreadPrime::ThreadProc));
    pmt1->Start();
    ThreadPrime^ pp2 = gcnew ThreadPrime();
    Thread^ pmt2 = gcnew Thread(gcnew ThreadStart(pp2, &ThreadPrime::ThreadProcPrimeNumber));
    Thread::Sleep(2);
    pmt2->Start();
    pmt2->Join();
    pmt1->Interrupt();
    pmt1->Join();
    ///*1*/   MessageBuffer^ m = gcnew MessageBuffer;

    ///*2a*/  ProcessMessages^ pm = gcnew ProcessMessages(m);
    ///*2b*/  Thread^ pmt = gcnew Thread(gcnew ThreadStart(pm,
    //    &ProcessMessages::ProcessMessagesEntryPoint));
    ///*2c*/  pmt->Start();

    ///*3a*/  CreateMessages^ cm = gcnew CreateMessages(m);
    ///*3b*/  Thread^ cmt = gcnew Thread(gcnew ThreadStart(cm,
    //    &CreateMessages::CreateMessagesEntryPoint));
    ///*3c*/  cmt->Start();

    ///*4*/   cmt->Join();
    ///*5*/   pmt->Interrupt();
    ///*6*/   pmt->Join();

    Console::WriteLine("Primary thread terminating");
}