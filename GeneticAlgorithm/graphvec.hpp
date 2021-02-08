//#pragma once
//#include"utils.hpp"
//#include<vector>
//#include<random>
//#include<map>
//#include<functional>
//#include<numeric>
//
//namespace ga
//{
//	enum class Color
//	{
//		COLOR_WHITE,COLOR_GRAY,COLOR_BLACK
//	};
//
//	struct ALLTOPO {};
//	ALLTOPO all_topo{};
//
//	template<typename T>
//	class Graph
//	{
//	public:
//		Graph(void) noexcept :adj_mat{}, enter_time{}, exit_time{}, time{}, topo_vec{}, dist{}, rand_device{}, rand_engine{}, all_topo_set{}, indegree_vec{}, discovered_vec{}, one_topo_vec{}
//		{
//			reset_color();
//		}
//		Graph(const Graph& graph) noexcept :adj_mat{}, enter_time{}, exit_time{}, time{}, topo_vec{}, dist{}, rand_device{}, rand_engine{}, all_topo_set{}, indegree_vec{}, discovered_vec{}, one_topo_vec{}
//		{
//			adj_mat = graph.adj_mat;
//		}
//		Graph(std::initializer_list<std::array<T, M>> list) :adj_mat{ list }, enter_time{}, exit_time{}, time{}, topo_vec{}, dist{}, rand_device{}, rand_engine{}, all_topo_set{}, indegree_vec{}, discovered_vec{}, one_topo_vec{} {}
//
//		Color color_at(size_t pos) const
//		{
//			if (pos > color.size()-1)
//				throw std::out_of_range("Vertex does not exist.");
//			return color[pos];
//		}
//		void set_color(size_t pos, Color color)
//		{
//			if(pos > this->color.size()-1)
//				throw std::out_of_range("Vertex does not exist.");
//			this->color[pos] = color;
//		}
//		void reset_color(void)
//		{
//			color.fill(Color::COLOR_WHITE);
//		}
//
//		std::set<std::vector<size_t>> all_topo(void)
//		{
//			init_indgree();
//			init_discovered();
//
//			dfs(::all_topo);
//
//			return all_topo_set;
//		}
//
//		std::vector<size_t> one_topo(void)
//		{
//			return dfs();
//		}
//
//		template<typename T, int M>
//		friend std::ostream& operator<<(std::ostream& ostream, Graph<T, M>& graph);
//		
//	private:
//		void dfs(ALLTOPO all_topo)
//		{
//			for (size_t i{}; i < indegree_vec.size(); i++)
//			{
//				if (indegree_vec[i] == 0 && !discovered_vec[i])
//				{
//					std::vector<size_t> out_vertex{ detect_out_vertex(i) };
//					decrease_indegree(out_vertex);
//					one_topo_vec.push_back(i);
//					discovered_vec[i] = true;
//
//					dfs(all_topo);
//
//					increase_indegree(out_vertex);
//					one_topo_vec.pop_back();
//					discovered_vec[i] = false;
//				}
//			}
//
//			if (one_topo_vec.size() == indegree_vec.size())
//			{
//				all_topo_set.insert(one_topo_vec);
//			}
//		}
//
//		void decrease_indegree(std::vector<size_t>& out_vertex)
//		{
//			std::for_each(std::begin(out_vertex), std::end(out_vertex), [this](auto& iter) {indegree_vec[iter]--; });
//		}
//
//		void increase_indegree(std::vector<size_t>& out_vertex)
//		{
//			std::for_each(std::begin(out_vertex), std::end(out_vertex), [this](auto& iter) {indegree_vec[iter]++; });
//		}
//
//		void init_indgree(void)
//		{
//			for (size_t i{}; i < indegree_vec.size(); i++)
//			{
//				for (size_t j{}; j < indegree_vec.size(); j++)
//				{
//					indegree_vec[j] += adj_mat[i][j];
//				}
//			}
//		}
//
//		void init_discovered(void)
//		{
//			discovered_vec.fill(false);
//		}
//
//		std::vector<size_t> dfs(void)
//		{
//			reset_color();
//			topo_vec.clear();
//			time = 0;
//			auto [m, n] = adj_mat.size();
//			std::vector<size_t> vertex(m);
//			std::iota(std::begin(vertex), std::end(vertex), 0);
//
//			while (!vertex.empty())
//			{
//				size_t rand_next_vertex = rand_vertex(vertex);
//				vertex.erase(std::find(std::begin(vertex), std::end(vertex), rand_next_vertex));
//				if (color[rand_next_vertex] == Color::COLOR_WHITE)
//				{
//					dfs_visit(rand_next_vertex);
//				}
//			}
//
//			time = 0;
//			return sort_exit_time();
//		}
//
//		std::vector<size_t> sort_exit_time(void)
//		{
//			std::map<unsigned int, size_t, std::greater<>> sort_map{};
//			for (size_t i{}; i < exit_time.size(); i++)
//			{
//				sort_map.insert(std::make_pair(exit_time[i], i));
//			}
//
//			std::vector<size_t> ret{};
//			std::for_each(std::begin(sort_map), std::end(sort_map), [&ret](auto& iter) {ret.push_back(iter.second); });
//
//			return ret;
//		}
//
//		void dfs_visit(size_t v)
//		{
//			time += 1;
//			enter_time[v] = time;
//			color[v] = Color::COLOR_GRAY;
//			
//			auto out_vertex = detect_out_vertex(v);
//			
//			while (!out_vertex.empty())
//			{
//				size_t rand_next_vertex = rand_vertex(out_vertex);
//				out_vertex.erase(std::find(std::begin(out_vertex), std::end(out_vertex), rand_next_vertex));
//				if (color[rand_next_vertex] == Color::COLOR_WHITE)
//				{
//					dfs_visit(rand_next_vertex);
//				}
//			}
//
//			color[v] = Color::COLOR_BLACK;
//			time += 1;
//			exit_time[v] = time;
//
//		}
//
//		std::vector<size_t> detect_out_vertex(size_t v)
//		{
//			std::vector<size_t> out_vertex{};
//			for (size_t i{}; i < adj_mat[v].size(); i++)
//			{
//				if (adj_mat[v][i] != 0)
//				{
//					out_vertex.push_back(i);
//				}
//			}
//
//			return out_vertex;
//		}
//
//		size_t rand_vertex(std::vector<size_t> out_vertex)
//		{
//			dist.param(std::uniform_int_distribution<>::param_type{ 0,static_cast<int>(out_vertex.size()-1) });
//			rand_engine.seed(rand_device());
//			return out_vertex[dist(rand_engine)];
//		}
//		size_t rand_vertex(size_t lb, size_t ub)
//		{
//			dist.param(std::uniform_int_distribution<>::param_type{ lb,ub });
//			rand_engine.seed(rand_device());
//			return dist(rand_engine);
//		}
//
//	private:
//		Mat<T, M, M> adj_mat;
//		std::array<unsigned int, M> enter_time;
//		std::array<unsigned int, M> exit_time;
//		std::array<Color, M> color;
//		unsigned int time;
//		std::vector<size_t> topo_vec;
//		std::uniform_int_distribution<int> dist;
//		std::random_device rand_device;
//		std::default_random_engine rand_engine;
//		std::set<std::vector<size_t>> all_topo_set;
//		std::array<T,M> indegree_vec;
//		std::array<bool, M> discovered_vec;
//		std::vector<size_t> one_topo_vec;
//	};
//
//	template<typename T>
//	std::set<std::vector<T>> operator+(std::set<std::vector<T>>& set, int num)
//	{
//		std::set<std::vector<T>> ret{};
//		std::vector<T> vec{};
//		for (auto& iter : set)
//		{
//			vec = iter;
//			for (auto& jter : vec)
//			{
//				jter += num;
//			}
//			ret.insert(vec);
//		}
//
//		return ret;
//	}
//
//	template<typename T, int M>
//	std::ostream& operator<<(std::ostream& ostream, Graph<T,M>& graph)
//	{
//		ostream << graph.adj_mat;
//		return ostream;
//	}
//	template<typename T>
//	std::ostream& operator<<(std::ostream& ostream, std::set<std::vector<T>> set)
//	{
//		ostream << "{" << std::endl;
//		for (auto& iter : set)
//		{
//			ostream << " [";
//			std::for_each(std::begin(iter), std::end(iter), [&ostream](auto& elem) {ostream << elem << ","; });
//			ostream << "\b" << "]" << std::endl;
//		}
//		ostream << "}" << std::endl;
//
//		return ostream;
//	}
//}