#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include <utility>

using std::priority_queue;
using std::vector;
using std::cin;
using std::cout;

typedef unsigned int ThreadID;
typedef long long TimeStamp;

class JThread
{
public:
	JThread(ThreadID id = -1, TimeStamp startingTime = 0);
	void takeJob(TimeStamp duration);
	bool operator< (const JThread& second) const;
	bool operator> (const JThread& second) const;
	bool operator<= (const JThread& second) const;
	bool operator>= (const JThread& second) const;
	bool operator== (const JThread& second) const;
	bool operator!= (const JThread& second) const;


	ThreadID getID();
	TimeStamp getStartingTime();

private:
	ThreadID id_;
	TimeStamp startingTime_;
};


class JobQueue {

public:
	JobQueue();
	~JobQueue();

	void Solve();

private:
	void WriteResponse() const;
	void ReadData();
	void AssignJobs();

	int num_workers_;
	vector<int> jobs_;
	priority_queue<JThread, std::vector<JThread>,std::greater<JThread>> threadHeap_;
	vector<std::pair<ThreadID, TimeStamp>> output;
};



JThread::JThread(ThreadID id, TimeStamp startingTime)
	:id_(id)
	, startingTime_(startingTime)
{
}


void JThread::takeJob(TimeStamp duration)
{
	startingTime_ += duration;
}


bool JThread::operator< (const JThread& second) const
{
	if (startingTime_ > second.startingTime_)
		return false;
	else if (startingTime_ < second.startingTime_)
		return true;

	return id_ < second.id_;
}


bool JThread::operator > (const JThread& second) const
{
	if (startingTime_ < second.startingTime_)
		return false;
	else if (startingTime_ > second.startingTime_)
		return true;

	return id_ > second.id_;
}


bool JThread::operator <= (const JThread& second) const
{
	return !(*this > second);
}


bool JThread::operator >= (const JThread& second) const
{
	return !(*this < second);
}


bool JThread::operator == (const JThread& second) const
{
	return (id_ == second.id_ && startingTime_ == second.startingTime_);
}


bool JThread::operator != (const JThread& second) const
{
	return !(*this == second);
}


ThreadID JThread::getID()
{
	return id_;
}


TimeStamp JThread::getStartingTime()
{
	return startingTime_;
}


JobQueue::JobQueue()
{
	num_workers_ = 0;
	jobs_.clear();
	threadHeap_;
	output.clear();
}

JobQueue::~JobQueue()
{
}


void JobQueue::Solve() {
	ReadData();
	AssignJobs();
	WriteResponse();
}


void JobQueue::WriteResponse() const {
	for (unsigned int i = 0; i < jobs_.size(); ++i) {
		cout << output.at(i).first << " " << output.at(i).second << "\n";
	}
}


void JobQueue::ReadData() {
	int m;
	cin >> num_workers_ >> m;
	jobs_.resize(m);
	output.resize(m);

	for (int i = 0; i < m; ++i)
		cin >> jobs_[i];

	for (int index = 0; index < num_workers_; index++)
	{
		JThread newThread(index);
		threadHeap_.push(newThread);
	}
}


void JobQueue::AssignJobs() {
	vector<long long> next_free_time(num_workers_, 0);
	for (int i = 0; i < jobs_.size(); ++i) {
		int duration = jobs_[i];
		auto thrd = threadHeap_.top();
		threadHeap_.pop();
		output.at(i) = std::pair<ThreadID, TimeStamp>(thrd.getID(), thrd.getStartingTime());
		JThread modifiedThread = JThread(thrd.getID(), thrd.getStartingTime());
		modifiedThread.takeJob(duration);
		threadHeap_.push(modifiedThread);
	}
}


int main() {
	JobQueue jobqueue;
	jobqueue.Solve();

	return 0;
}
