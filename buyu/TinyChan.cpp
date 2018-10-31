#include "TinyChan.h"

Chan::Chan()
{
	isRef = false;
}


Chan::~Chan()
{
	if (data != NULL && !isRef) {
		delete data;
		data = NULL;
	}
}
int Chan::ConverToInt() {

	int* o = (int*)data;

	int i = *o;

	delete o;

	data = NULL;

	return i;
}
float Chan::ConverToFloat() {

	float* o = (float*)data;

	float f = *o;

	delete o;

	data = NULL;

	return f;
}
bool Chan::ConverToBool() {

	bool* o = (bool*)data;

	bool b = *o;

	delete o;

	data = NULL;

	return b;
}

TinyChan::TinyChan()
{
}


TinyChan::~TinyChan()
{
	Reset();
}
void TinyChan::Reset() {

	while (!IsEmpty())
	{
		auto  c = PopGameChan();
		if (c != NULL) {
			delete c;
		}
	}
}
void TinyChan::PushGameChan(Chan* c)
{
	mutex_chan_.lock();
	this->GameChan.push(c);
	mutex_chan_.unlock();
}
void  TinyChan::PushGameChan(ChanType t, void* d, bool isRef) {

	Chan* c = new(nothrow) Chan;
	if (c && d) {
		c->type = t;
		c->data = d;
		c->isRef = isRef;
		mutex_chan_.lock();
		this->GameChan.push(c);
		mutex_chan_.unlock();
	}
	
}

Chan* TinyChan::PopGameChan()
{
	mutex_chan_.lock();
	auto  top = this->GameChan.front();
	this->GameChan.pop();
	mutex_chan_.unlock();
	return top;
}
bool TinyChan::IsEmpty() {

	mutex_chan_.lock();

	bool empty = GameChan.empty();

	mutex_chan_.unlock();

	return empty;
}