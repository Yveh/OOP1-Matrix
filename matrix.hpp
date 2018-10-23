#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu
{
	
	template <class T>
	class Matrix
	{
	private:
		size_t n, m;
		T *arr;
		// your private member variables here.
		
	public:
		Matrix() = default;
		
		Matrix(size_t _n, size_t _m, T _init = T())
		{
			n = _n;
			m = _m;
			arr = new T[n * m];
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] = _init;
		}
		
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
		{
			n = sz.first;
			m = sz.second;
			arr = new T[n * m];
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] = _init;
		}
		
		Matrix(const Matrix &o)
		{
			n = o.n;
			m = o.m;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] = o.arr[i * n + j];
		}
		
		template <class U>
		Matrix(const Matrix<U> &o)
		{
			n = o.n;
			m = o.m;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] = o.arr[i * n + j];
		}
		
		Matrix &operator=(const Matrix &o)
		{
			n = o.n;
			m = o.m;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] = o.arr[i * n + j];
			return *this;
		}
		
		template <class U>
		Matrix &operator=(const Matrix<U> &o)
		{
			n = o.n;
			m = o.m;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] = o.arr[i * n + j];
			return *this;
		}
		
		Matrix(Matrix &&o) noexcept
		{
			n = o.n;
			m = o.m;
			delete []arr;
			arr = o.arr;
			o.arr = nullptr;
		}
		
		Matrix &operator=(Matrix &&o) noexcept
		{
			n = o.n;
			m = o.m;
			delete []arr;
			arr = o.arr;
			o.arr = nullptr;
			return *this;
		}
		
		~Matrix()
		{
			delete []arr;
		}
		
		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
			n = il.size();
			m = il.begin()->size();
			arr = new T[n * m];
			int i = 0, j;
			for (auto ii : il)
			{
				j = 0;
				for (auto jj : ii)
				{
					arr[i * n + j] = jj;
					j++;
				}
				i++;
			}
		}
		
	public:
		size_t rowLength() const
		{
			return n;
		}
		
		size_t columnLength() const
		{
			return m;
		}
		
		void resize(size_t _n, size_t _m, T _init = T())
		{
			if (n != _n || m != _m)
			{
				T *tmp = new T[_n * _m];
				for (int i = 0; i < _n; i++)
					for (int j = 0; j < _m; j++)
						if (i < n && j < m)
							tmp[i * n + j] = arr[i * n + j];
						else
							tmp[i * n + j] = _init;
				delete []arr;
				arr = tmp;
				n = _n;
				m = _m;
			}
		}
		
		void resize(std::pair<size_t, size_t> sz, T _init = T())
		{
			if (n != sz.first || m != sz.second)
			{
				T *tmp = new T[sz.first * sz.second];
				for (int i = 0; i < sz.first; i++)
					for (int j = 0; j < sz.second; j++)
						if (i < n && j < m)
							tmp[i * n + j] = arr[i * n + j];
						else
							tmp[i * n + j] = _init;
				delete []arr;
				arr = tmp;
				n = sz.first;
				m = sz.second;
			}
		}
		
		std::pair<size_t, size_t> size() const
		{
			return std::make_pair(n, m);
		}
		
		void clear()
		{
			delete []arr;
		}
		
	public:
		const T &operator()(size_t i, size_t j) const
		{
			return arr[i * n + j];
		}
		
		T &operator()(size_t i, size_t j)
		{
			return arr[i * n + j];
		}
		
		Matrix<T> row(size_t i) const
		{
			Matrix<T> ret;
			ret.n = 1;
			ret.m = m;
			ret.arr = new T[ret.n * ret.m];
			for (int j = 0; j < m; j++)
				ret.arr[j] = arr[i * n + j];
			return ret;
		}
		
		Matrix<T> column(size_t j) const
		{
			Matrix<T> ret;
			ret.n = n;
			ret.m = 1;
			ret.arr = new T[ret.n * ret.m];
			for (int i = 0; i < n; i++)
				ret.arr[i] = arr[i * n + j];
			return ret;
		}
		
		
	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const
		{
			if (n != o.n || m != o.m) return false;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					if (arr[i * n + j] != o.arr[i * n + j])
						return false;
			return true;
		}
		
		template <class U>
		bool operator!=(const Matrix<U> &o) const
		{
			if (n != o.n || m != o.m) return true;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					if (arr[i * n + j] != o.arr[i * n + j])
						return true;
			return false;
		}
		
		Matrix operator-() const
		{
			Matrix ret(*this);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					ret.arr[i * n + j] = -ret.arr[i * n + j];
			return ret;
		}
		
		template <class U>
		Matrix &operator+=(const Matrix<U> &o)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] += o.arr[i * n + j];
			return *this;
		}
		
		template <class U>
		Matrix &operator-=(const Matrix<U> &o)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] -= o.arr[i * n + j];
			return *this;
		}
		
		template <class U>
		Matrix &operator*=(const U &x)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					arr[i * n + j] *= x;
			return *this;
		}
		
		Matrix tran() const
		{
			Matrix ret(*this);
			for (int i = 0; i < n; i++)
				for (int j = i + 1; j < m; j++)
					swap(ret.a[i * n + j], ret.a[j * n + i]);
			swap(ret.n, ret.m);
			return ret;
		}
		
	public: // iterator
		class iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type        = T;
			using pointer           = T *;
			using reference         = T &;
			using size_type         = size_t;
			using difference_type   = std::ptrdiff_t;
			
			iterator() = default;
			
			iterator(const iterator &) = default;
			
			iterator &operator=(const iterator &) = default;
			
		private:
			pointer *px, *py;
			
		public:
			difference_type operator-(const iterator &o)
			{
				// return ;
			}
			
			iterator &operator+=(difference_type offset)
			{
				// p += offset;
				// return *this;
			}
			
			iterator operator+(difference_type offset) const
			{
				// iterator ret;
				// ret.p = p + offset;
				// return ret;
			}
			
			iterator &operator-=(difference_type offset)
			{
				// p -= offset;
				// return *this;
			}
			
			iterator operator-(difference_type offset) const
			{
				// iterator ret;
				// ret.p = p + offset;
				// return ret;
			}
			
			iterator &operator++()
			{
				// p++;
				// return *this;
			}
			
			iterator operator++(int)
			{
				// iterator ret;
				// ret.p = p + 1;
				// return ret;
			}
			
			iterator &operator--()
			{
				// p--;
				// return *this;
			}
			
			iterator operator--(int)
			{
				// iterator ret;
				// ret.p = p - 1;
				// return ret;
			}
			
			reference operator*() const
			{
				// return *p;
			}
			
			pointer operator->() const
			{
				// return p;
			}
			
			bool operator==(const iterator &o) const
			{
				// return p == o.p;
			}
			
			bool operator!=(const iterator &o) const
			{
				// return p != o.p;
			}
		};
		
		iterator begin()
		{
			// iterator ret;
			// ret.p = arr;
			// return ret;
		}
		
		iterator end()
		{
			// iterator ret;
			// ret.p = arr + n * m;
			// return ret;
		}
		
		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
		{
			// pair<iterator, iterator> ret;
			// ret.first.p = arr + l.first 
        }
	};
		
}

//
namespace sjtu
{
	template <class T, class U>
	auto operator*(const Matrix<T> &mat, const U &x)->decltype(Matrix<T * U>)
	{
		Matrix(decltype(T * U))
	}
	
	template <class T, class U>
	auto operator*(const U &x, const Matrix<T> &mat)
	{
		
	}
	
	template <class U, class V>
	auto operator*(const Matrix<U> &a, const Matrix<V> &b)
	{
		
	}
	
	template <class U, class V>
	auto operator+(const Matrix<U> &a, const Matrix<V> &b)
	{
		
	}
	
	template <class U, class V>
	auto operator-(const Matrix<U> &a, const Matrix<V> &b)
	{
		
	}
	
}

#endif //SJTU_MATRIX_HPP

