#pragma once
#include<algorithm>
#include<array>
#include<tuple>
#include<stdexcept>
#include<algorithm>
#include<initializer_list>
#include<string>
#include<fstream>

namespace ga
{
	template<typename T, int M, int N>
	class Mat
	{
	public:
		Mat(void) noexcept :mat{} {}
		Mat(const Mat& lhr)
		{
			mat = lhr.mat;
		}
		Mat(std::initializer_list<std::array<T, N>> list) :mat{}
		{
			auto iter = std::begin(list);
			for (size_t i{}; i < list.size(); i++, ++iter)
			{
				mat[i] = *iter;
			}
		}

		void fill(T num)
		{
			for (auto& row : mat)
			{
				row.fill(num);
			}
		}

		std::tuple<size_t, size_t> size(void) const
		{
			return std::make_tuple(mat.size(), mat[0].size());
		}

		std::array<T,N>& operator[](size_t n)
		{
			return mat[n];
		}

		bool operator==(const Mat& lhr)
		{
			for (size_t m{}; m < mat.size(); m++)
			{
				for (size_t n{}; n < mat[0].size(); n++)
				{
					if (mat[m][n] != lhr.mat[m][n])
					{
						return false;
					}
				}
			}

			return true;
		}

		template<typename T, int M, int N>
		friend bool operator==(const Mat<T,M,N>& mat1, const Mat<T,M,N>& mat2);
		template<typename T, int M, int N>
		friend std::ostream& operator<<(std::ostream& ostream, Mat<T, M, N>& mat);
	private:
		std::array<std::array<T,N>,M> mat;
	};

	template<typename T,int M,int N>
	bool operator==(const Mat<T,M,N>& mat1, const Mat<T,M,N>& mat2)
	{
		auto [m1, n1] = mat1.size();
		auto [m2, n2] = mat2.size();

		if (m1 != m2 || n1 != n2)
		{
			throw std::length_error{ "Mat size not match" };
		}

		for (size_t m{}; m < mat1.mat.size(); m++)
		{
			for (size_t n{}; n < mat1.mat[0].size(); n++)
			{
				if (mat1.mat[m][n] != mat2.mat[m][n])
				{
					return false;
				}
			}
		}

		return true;
	}

	template<typename T, int M, int N>
	std::ostream& operator<<(std::ostream& ostream, Mat<T, M, N>& mat)
	{
		ostream << "[" << std::endl;
		for (auto& row : mat.mat)
		{
			ostream << " [";
			std::copy(std::begin(row), std::end(row), std::ostream_iterator<T>(ostream, ","));
			ostream << "\b" << "]," << std::endl;
		}
		ostream << "]" << std::endl;

		return ostream;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& ostream, std::vector<T>& vec)
	{
		ostream << "[";
		std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<T>(ostream, ","));
		ostream << "\b" << "]" << std::endl;

		return ostream;
	}
	//template<typename T>
	//std::ostream& operator<<(std::ostream& ostream, std::vector<T>&& vec)
	//{
	//	ostream << "[";
	//	std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<T>(ostream, ","));
	//	ostream << "\b" << "]" << std::endl;

	//	return ostream;
	//}

	template<typename T>
	std::ostream& operator<<(std::ostream& ostream, std::vector<T>&& vec)
	{
		return operator<<(ostream, vec);
	}
	template<typename T>
	std::vector<T> operator+(std::vector<T>& vec, T&& num)
	{
		std::vector<T> ret{};
		std::for_each(std::begin(vec), std::end(vec), [&ret,&num](auto& iter) {ret.push_back(iter + num); });

		return ret;
	}
	template<typename T>
	std::vector<T> operator+(std::vector<T>&& vec, T&& num)
	{
		return operator+(vec,std::forward<T>(num));
	}
	template<typename T>
	std::ostream& operator<<(std::ostream& ostream, std::vector<std::vector<T>>& vec)
	{
		ostream << "[" << std::endl;
		for (auto& row : vec)
		{
			ostream << " [";
			std::copy(std::begin(row), std::end(row), std::ostream_iterator<T>(ostream, ","));
			ostream << "\b" << "]" << std::endl;
		}
		ostream << "]" << std::endl;

		return ostream;
	}

	class Reader
	{
	public:
		Reader(std::string filename)
		{
			file.open(filename, std::ios_base::in);
		}

		~Reader(void)
		{
			file.close();
		}
	private:
		std::vector<std::vector<size_t>> read_file(void)
		{
			std::string line{};
			size_t column_count{ count_column() };
			std::vector<std::string> str_vec{};
			std::vector<std::vector<size_t>> mat{};
			std::vector<size_t> row{};

			while (!file.eof())
			{
				std::getline(file, line);
				line.push_back(',');
				str_vec = split(line, ',');
				std::transform(std::begin(str_vec), std::end(str_vec), std::back_inserter(row), [](auto iter) {return std::stoi(iter); });
				mat.push_back(row);
				row.clear();
			}

			return mat;
		}
		std::vector<std::string> split(std::string str, char delim)
		{
			std::string buffer{};
			std::vector<std::string> str_vec{};
			std::for_each(std::begin(str), std::end(str), [&buffer, &str_vec, &delim](auto& ch) {if (ch != delim) { buffer.push_back(ch); } else { str_vec.push_back(buffer); buffer.clear(); }});

			return str_vec;
		}
		size_t count_column(void)
		{
			std::string line{};
			std::getline(file, line);
			size_t column_count{1};
			std::for_each(std::begin(line), std::end(line), [&column_count](auto& iter) {if (iter == ',') column_count++; });
			file.seekg(0);

			return column_count;
		}
	private:
		std::ifstream file;
	};
}