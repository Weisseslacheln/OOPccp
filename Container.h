#pragma once

class ErrorMessage
{
public:
	char *err;
	int nomer;

	int Send_error()
	{
		std::cout << err << std::endl;
		return nomer;
	}
};

template<typename T>
class Container {
public:
	Container() {
		m_first = NULL;
		m_last = NULL;
		m_kolvo = 0;
	}

	~Container() {
		Clear();
	}

	T & operator [] ( int i ) const {
		Node * node = m_first;
		if(( i >= 0 ) && ( i < m_kolvo )) {
			for( int j = 1; j <= i; j++ ) {
				node = node-> m_next;
			}
			return node-> m_data;
		}
		else {
			throw ErrorMessage{ "Index larger than Container size.", -1 };
		}
	}

	bool IsItEmpty() {
		return m_kolvo == 0;
	}

	void PushFirst(T const & data) {
		Node * new_node = new Node;
		new_node -> m_data = data;
		if( !IsItEmpty() ) {
			new_node -> m_next = m_first;
			m_first -> m_prev = new_node;
		}
		else {
			new_node -> m_next = NULL;
			m_last = new_node;
		}
		m_first = new_node;
		m_first -> m_prev = NULL;
		m_kolvo++;
	}

	void PushLast(T const & data) {
		Node * new_node = new Node;
		new_node -> m_data = data;
		if( !IsItEmpty() ) {
			m_last -> m_next = new_node;
			new_node -> m_prev = m_last;
		}
		else {
			new_node -> m_prev = NULL;
			m_first = new_node;
		}
		m_last = new_node;
		m_last -> m_next = NULL;
		m_kolvo++;
	}
	
	T RemoveAndGetFirst() {
		if( !IsItEmpty() ) {
			Node * new_node = m_first;
			T data = new_node -> m_data;
			m_first = new_node -> m_next;
			if( m_first != NULL )
				m_first -> m_prev = NULL;
			delete new_node;
			m_kolvo--;
			return data;
		}
		else {
			throw ErrorMessage{ "Nothing to remove, Container is empty.", -2 };
		}
	}
	
	T RemoveAndGetLast() {
		if( !IsItEmpty() ) {
			Node * new_node = m_last;
			T data = new_node -> m_data;
			m_last = new_node -> m_prev;
			if(m_last != NULL )
				m_last -> m_next = NULL;
			delete new_node;
			m_kolvo--;
			return data;
		}
		else {
			throw ErrorMessage{ "Nothing to remove, Container is empty.", -2 };
		}
	}

	void Clear() {
		if (m_kolvo % 2 == 1) {
			RemoveAndGetLast();
		}
		while (!IsItEmpty()) {
			RemoveAndGetLast();
			RemoveAndGetFirst();
		}
	}

	int Current_Size() const {
		return m_kolvo;
	}

	T & First() {
		if( !IsItEmpty() ) {
			return m_first -> m_data;
		}
		else {
			throw ErrorMessage{ "Nothing to get, Container is empty.", -3 };
		}
	}

	T & Last() {
		if( !IsItEmpty() ) {
			return m_last -> m_data;
		}
		else {
			throw ErrorMessage{ "Nothing to get, Container is empty.", -3 };
		}
	}

	private:
		struct Node {
			T m_data;
			Node * m_next;
			Node * m_prev;
		};
		Node * m_first;
		Node * m_last;
		int m_kolvo;
};
