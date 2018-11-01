#include <iostream>
using namespace std;
enum Error_code { underflow, overflow, range_error, success, fail};
const int max_list = 30;
template < class List_entry>
class List {
public:
	List();
	int size() const;
	bool full() const;
	bool empty() const;
	void clear();
	void print();
	void traverse(void(*visit)(List_entry &));
	Error_code retrieve(int position, List_entry &x) const;
	Error_code replace(int position, const List_entry &x);
	Error_code remove(int position, List_entry &x);
	Error_code insert(int position, const List_entry &x);
protected:
	// data members for a contiguous list implementation
	int count;
	List_entry entry[max_list];
};
template<class List_entry>
List<List_entry>::List()
{
	count = 0;
}
template < class List_entry>
int List<List_entry>::size()const {
	return count;
}
template < class List_entry>
bool List<List_entry>::full()const {
	return count == max_list;
}
template < class List_entry>
bool List<List_entry>::empty()const {
	return count == 0;
}
template < class List_entry>
void List<List_entry>::clear() {
	count = 0;
}
template < class List_entry>
void List<List_entry>::print() {
	for (int i = 0;i < count;++i) {
		cout << entry[i] << " ";
	}
}
template < class List_entry>
void List<List_entry>::traverse(void(*visit)(List_entry&)) {
	for (int i = 0;i < count;++i)
		(*visit)(entry[i]);
}
template < class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const {
	if (empty())
		return underflow;
	if (position < 0 || position >= count)
		return range_error;
	x = entry[position];
	return success;
}
template < class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x) {
	if (empty())
		return underflow;
	if (position < 0 || position >= count)
		return range_error;
	entry[position] = x;
	return success;
}
template < class List_entry>
Error_code remove(int position, List_entry &x) {
	if (empty())
		return underflow;
	if (position < 0 || position >= count)
		return range_error;
	x=entry[position];
	for (int i = position;i < count;i++) {
		entry[i] = entry[i + 1];
	}
	count--;
	return success;
}
template < class List_entry>
Error_code insert(int position, const List_entry &x) {
	if (full())
		return overflow;
	if (position<0 || position>count)
		return range_error;
	for (int i = count - 1;i >= position;i--) 
		entry[i + 1] = entry[i];
	entry[position] = x;
	count++;
	return success;
}
typedef int Key;
class Key {
	int key;
public:
	Key(int x = 0);
	int the_key()const;
};
bool operator>(const Key&x, const Key&y);
bool operator<(const Key&x, const Key&y);
bool operator<=(const Key&x, const Key&y);
bool operator>=(const Key&x, const Key&y);
bool operator==(const Key&x, const Key&y);
bool operator!=(const Key&x, const Key&y);
ostream&operator<<(ostream&output, Key&x);
bool operator>(const Key&x, const Key&y) {
	return x.the_key() > y.the_key();
}
bool operator<(const Key&x, const Key&y) {
	return x.the_key() < y.the_key();
}
bool operator<=(const Key&x, const Key&y) {
	return x.the_key() <=y.the_key();
}
bool operator>=(const Key&x, const Key&y) {
	return x.the_key()>=y.the_key();
}
bool operator==(const Key&x, const Key&y) {
	return x.the_key()==y.the_key();
}
bool operator!=(const Key&x, const Key&y) {
	return x.the_key()!=y.the_key();
}
ostream&operator<<(ostream&output, Key&x) {
	output << x.the_key() << endl;
}
class Ordered_list : public List<Key> {
public:
	Error_code insert(const Key &data);
	Error_code insert(int position, const Key &data);
	Error_code replace(int position, const Key &data);
};
Error_code Ordered_list::insert(const Key &data) {
	int s = size();
	int position;
	for (position = 0;position < s;position++) {
		Key list_data;
		retrieve(position, list_data);
		if (data >= list_data);break;
	}
	return List<Key>::insert(position, data);
}
Error_code Ordered_list::insert(int position, const Key &data) {
	Key list_data;
	if (position > 0) {
		retrieve(position - 1, list_data);
		if (data < list_data)
			return fail;
	}
	if (position < size()) {
		retrieve(position, list_data);
		if (data > list_data)
			return fail;
	}
	return List<Key>::insert(position, data);
}
Error_code Ordered_list::replace(int position, const Key &data) {
	Key list_data;
	if (position > 0) {
		retrieve(position - 1,list_data);
		if (data <list_data)
			return fail;
	}
	if (position < size() - 1) {
		retrieve(position + 1,list_data);
		if (data > list_data)
			return fail;
	}
	return List<Key>::replace(position, data);
}
int main() {
	List<int> mylist;
	cout << mylist.empty() << endl;
	mylist.insert(0, 23);
	mylist.insert(0, 25);
	mylist.insert(0, 7);
	mylist.insert(0, 83);
	mylist.insert(0, 23);
	mylist.insert(0, 13);
	mylist.insert(0, 28);
	cout << mylist.empty() << endl;
	mylist.print();
	Ordered_list my;
	cout << endl << my.empty() << endl;
	my.insert(29);
	my.insert(5);
	my.insert(7);
	my.insert(1);
	my.insert(0);
	my.insert(70);
	my.print();
}


