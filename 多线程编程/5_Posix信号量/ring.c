#include"ring.h"

void init_ring(ring_ptr _r)
{
	if(_r){
		_r->prev = 0;
		_r->curr = 0;
		_r->count = 0;
		memset(_r->ring_buf, 0, sizeof(_r->ring_buf));
	}
}

static int is_empty(ring_ptr _r)
{
	return _r && _r->count ==0 ? _TRUE_:_FALSE_;
}

static int is_full(ring_ptr _r)
{
	return _r && _r->count == _SIZE_ ? _TRUE_:_FALSE_;
}

int put_data(ring_ptr _r, elem_type data)
{
	if(!is_full()){
		_r->ring_buf[_r->curr++] = data;
		_r->count++;
		_r->curr %= _SIZE_;
		return _TRUE_;
	}
	return _FALSE_;
}

int get_data(elem_type *_data_p)
{
	if(!is_empty()){
		*_data_p = _r->ring_buf[_r->prev++] ;
		_r->count--;
		_r->prev = r->prev % _SIZE_;
		return _TRUE_;
	}
	return _FALSE_;
}

void show_buff(ring_ptr _r)
{
	int index = 0;
	while(index < _r->count){
		printf("%d\n",_r->buf[_r->prev+index]%_SIZE_);
		++index;
	}
}