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
		Matrix(size_t _n = 0, size_t _m = 0, T _init = T())
		{
			n = _n;
			m = _m;
			arr = new T[n * m];
			printf("%d %d\n", _n, _m);
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] = _init;
		}
		
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
		{
			n = sz.first;
			m = sz.second;
			arr = new T[n * m];
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] = _init;
		}
		
		Matrix(const Matrix &o)
		{
			n = o.rowLength();
			m = o.columnLength();
			arr = new T[n * m];
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] = o(i, j);
		}
		
		template <class U>
		Matrix(const Matrix<U> &o)
		{
			n = o.rowLength();
			m = o.columnLength();
			arr = new T[n * m];
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] = o(i, j);
		}
		
		Matrix &operator=(const Matrix &o)
		{
			n = o.rowLength();
			m = o.columnLength();
			T *tmp = new T[n * m];
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					tmp[i * m + j] = o(i, j);
			delete []arr;
			arr = tmp;
			return *this;
		}
		
		template <class U>
		Matrix &operator=(const Matrix<U> &o)
		{
			n = o.rowLength();
			m = o.columnLength();
			arr = new T[n * m];
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] = o(i, j);
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
			delete [] arr;
		}
		
		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
			n = il.size();
			m = il.begin()->size();
			arr = new T[n * m];
			size_t i = 0, j;
			for (auto ii : il)
			{
				j = 0;
				for (auto jj : ii)
				{
					arr[i * m + j] = jj;
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
				for (size_t i = 0; i < _n; i++)
					for (size_t j = 0; j < _m; j++)
						if (i < n && j < m)
							tmp[i * m + j] = arr[i * m + j];
						else
							tmp[i * m + j] = _init;
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
				for (size_t i = 0; i < sz.first; i++)
					for (size_t j = 0; j < sz.second; j++)
						if (i < n && j < m)
							tmp[i * m + j] = arr[i * m + j];
						else
							tmp[i * m + j] = _init;
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
			return arr[i * m + j];
		}
		
		T &operator()(size_t i, size_t j)
		{
			return arr[i * m + j];
		}
		
		Matrix<T> row(size_t i) const
		{
			Matrix<T> ret(1, m);
			for (size_t j = 0; j < m; j++)
				ret.arr[j] = arr[i * m + j];
			return ret;
		}
		
		Matrix<T> column(size_t j) const
		{
			Matrix<T> ret(n, 1);
			for (size_t i = 0; i < n; i++)
				ret.arr[i] = arr[i * m + j];
			return ret;
		}
		
		
	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const
		{
			if (n != o.rowLength() || m != o.columnLength()) return false;
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					if (arr[i * m + j] != o(i, j))
						return false;
			return true;
		}
		
		template <class U>
		bool operator!=(const Matrix<U> &o) const
		{
			if (n != o.rowLength() || m != o.columnLength()) return true;
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					if (arr[i * m + j] != o(i, j))
						return true;
			return false;
		}
		
		Matrix operator-() const
		{
			Matrix ret(*this);
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					ret.arr[i * m + j] = -ret.arr[i * m + j];
			return ret;
		}
		
		template <class U>
		Matrix &operator+=(const Matrix<U> &o)
		{
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] += o.arr[i * m + j];
			return *this;
		}
		
		template <class U>
		Matrix &operator-=(const Matrix<U> &o)
		{
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] -= o.arr[i * m + j];
			return *this;
		}
		
		template <class U>
		Matrix &operator*=(const U &x)
		{
			for (size_t i = 0; i < n; i++)
				for (size_t j = 0; j < m; j++)
					arr[i * m + j] *= x;
			return *this;
		}
		
		Matrix tran() const
		{
			Matrix ret(*this);
			for (size_t i = 0; i < n; i++)
				for (size_t j = i + 1; j < m; j++)
					std::swap(ret.arr[i * m + j], ret.arr[j * n + i]);
			std::swap(ret.n, ret.m);
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
			
			iterator(const pointer &o)
			{
				p = o;
			}
			
			iterator(const iterator &o)
			{
				p = o.p;
			}
			
			iterator &operator=(const iterator &o)
			{
				p = o.p;
				return *this;
			}
			
		private:
			pointer p;
			
		public:
			difference_type operator-(const iterator &o)
			{
				return p - o.p;
			}
			
			iterator &operator+=(difference_type offset)
			{
				p += offset;
				return *this;
			}
			
			iterator operator+(difference_type offset) const
			{
				iterator ret(p + offset);
				return ret;
			}
			
			iterator &operator-=(difference_type offset)
			{
				p -= offset;
				return *this;
			}
			
			iterator operator-(difference_type offset) const
			{
				iterator ret(p - offset);
				return ret;
			}
			
			iterator &operator++()
			{
				p++;
				return *this;
			}
			
			iterator operator++(int)
			{
				p++;
				return *this;
			}
			
			iterator &operator--()
			{
				p--;
				return *this;
			}
			
			iterator operator--(int)
			{
				p--;
				return *this;
			}
			
			reference operator*() const
			{
				return *p;
			}
			
			pointer operator->() const
			{
				return p;
			}
			
			bool operator==(const iterator &o) const
			{
				return p == o.p;
			}
			
			bool operator!=(const iterator &o) const
			{
				return p != o.p;
			}
		};
		
		iterator begin()
		{
			iterator ret(arr);
			return ret;
		}
		
		iterator end()
		{
			iterator ret(arr + n * m);
			return ret;
		}
		
		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
		{
			Matrix<T> *ret = new Matrix<T>(r.first - l.first + 1, r.second - l.second + 1);
			size_t c = 0;
			for (size_t i = l.first; i <= r.first; i++)
				for (size_t j = l.second; j <= r.second; j++, c++)
					ret->arr[c] = arr[i * m + j];
			return std::make_pair(ret->begin(), ret->end());
        }
	};
		
}

//
namespace sjtu
{
	template <class T, class U>
	auto operator*(const Matrix<T> &mat, const U &x)->Matrix<decltype(T() * U())>
	{
		Matrix<decltype(T() * U())> ret(mat.rowLength(), mat.columnLength());
		for (size_t i = 0; i < ret.rowLength(); i++)
			for (size_t j = 0; j < ret.columnLength(); j++)
				ret(i, j) *= x;
		return ret;
	}
	
	template <class T, class U>
	auto operator*(const U &x, const Matrix<T> &mat)->Matrix<decltype(U() * T())>
	{
		Matrix<decltype(U() * T())> ret(mat.rowLength(), mat.columnLength());
		for (size_t i = 0; i < ret.rowLength(); i++)
			for (size_t j = 0; j < ret.columnLength(); j++)
				ret(i, j) *= x;
		return ret;
	}
	
	template <class U, class V>
	auto operator*(const Matrix<U> &a, const Matrix<V> &b)->Matrix<decltype(U() * V())>
	{
		Matrix<decltype(U() * V())> ret(a.rowLength(), b.columnLength());
		for (size_t i = 0; i < a.rowLength(); i++)
			for (size_t j = 0; j < a.columnLength(); j++)
				for (size_t k = 0; k < b.columnLength(); k++)
					ret(i, k) += a(i, j) * b(j, k);
		return ret;
	}
	
	template <class U, class V>
	auto operator+(const Matrix<U> &a, const Matrix<V> &b)->Matrix<decltype(U() + V())>
	{
		Matrix<decltype(U() * V())> ret(a.rowLength(), a.columnLength());
		for (size_t i = 0; i < a.rowLength(); i++)
			for (size_t j = 0; j < a.columnLength(); j++)
				ret(i, j) = a(i, j) + b(i, j);
		return ret;
	}
	
	template <class U, class V>
	auto operator-(const Matrix<U> &a, const Matrix<V> &b)->Matrix<decltype(U() - V())>
	{
		Matrix<decltype(U() * V())> ret(a.rowLength(), a.columnLength());
		for (size_t i = 0; i < a.rowLength(); i++)
			for (size_t j = 0; j < a.columnLength(); j++)
				ret(i, j) = a(i, j) - b(i, j);
		return ret;
	}
	
}

#endif //SJTU_MATRIX_HPP

