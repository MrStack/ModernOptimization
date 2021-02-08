#include"gtest/gtest.h"
#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
#define private public
#endif

#include"utils.hpp"
#include"ga.hpp"
#include"graphvec.hpp"


#include<vector>
#include<set>

using namespace ga;




TEST(MatTest, InitMat)
{
	Mat<int,2,3> mat1{ {1,2,3},{4,5,6} };
	Mat<int,2,3> mat2{ {1,2,3},{4,5,6} };

	EXPECT_EQ(mat1, mat2);
}

TEST(MatTest, IndexTest)
{
	Mat<int, 2, 3> mat{ {1,3,4},{2,5,6} };

	EXPECT_EQ(mat[0][0], 1);
	EXPECT_EQ(mat[0][1], 3);
	EXPECT_EQ(mat[0][2], 4);
	EXPECT_EQ(mat[1][0], 2);
	EXPECT_EQ(mat[1][1], 5);
	EXPECT_EQ(mat[1][2], 6);
}

TEST(MatTest, ReturnRow)
{
	Mat<int, 2, 2> mat{ {1,1},{2,2} };

	std::array<int, 2> fr{ 1,1 };
	std::array<int, 2> sr{ 2,2 };
	EXPECT_EQ(mat[0], fr);
	EXPECT_EQ(mat[1], sr);
}

TEST(MatTest, FillTest)
{
	Mat<int, 2, 2> mat{};

	mat.fill(1);

	EXPECT_EQ(mat[0][0], 1);
	EXPECT_EQ(mat[0][1], 1);
	EXPECT_EQ(mat[1][0], 1);
	EXPECT_EQ(mat[1][1], 1);
}

TEST(MatTest, OutputTest)
{
	Mat<int, 3, 3> mat{};
	mat.fill(3);

	std::cout << mat << std::endl;	
}

TEST(GraphTest, InitColorTest)
{
	Graph<int, 2> graph{};

	EXPECT_EQ(graph.color_at(0), Color::COLOR_WHITE);
	EXPECT_EQ(graph.color_at(1), Color::COLOR_WHITE);
}

TEST(GraphTest, ColorOutOfRange)
{
	Graph<int, 2> graph{};

	EXPECT_THROW(graph.color_at(2), std::out_of_range);
}

TEST(GraphTest, SetColorTest)
{
	Graph<int, 2> graph{};

	graph.set_color(0, Color::COLOR_GRAY);
	graph.set_color(1, Color::COLOR_BLACK);
	EXPECT_EQ(graph.color_at(0), Color::COLOR_GRAY);
	EXPECT_EQ(graph.color_at(1), Color::COLOR_BLACK);
}

TEST(GraphTest, ResetColorTest)
{
	Graph<int, 2> graph{};

	graph.set_color(0, Color::COLOR_GRAY);
	graph.set_color(1, Color::COLOR_BLACK);
	graph.reset_color();
	EXPECT_EQ(graph.color_at(0), Color::COLOR_WHITE);
	EXPECT_EQ(graph.color_at(1), Color::COLOR_WHITE);
}

TEST(GraphTest, RandGenTest)
{
	Graph<int, 10> graph{};

	std::vector<size_t> out_vertex{ 2,3,4,5,7,8 };
	size_t rand = graph.rand_vertex(out_vertex);
	auto p = std::find(std::begin(out_vertex), std::end(out_vertex), rand);
	EXPECT_NE(p, std::end(out_vertex));
}

TEST(GraphTest, RandOutVertex)
{
	Graph<int, 11> graph{
	//   0 1 2 3 4 5 6 7 8 9 10
		{0,1,1,1,1,0,0,0,0,0,0},//0
		{0,0,0,0,0,1,0,0,0,0,0},//1
		{0,0,0,0,0,0,1,0,0,0,0},//2
		{0,0,0,0,0,0,1,0,0,0,0},//3
		{0,0,0,0,0,0,1,0,0,0,0},//4
		{0,0,0,0,0,0,0,1,0,0,0},//5
		{0,0,0,0,0,0,0,0,1,0,0},//6
		{0,0,0,0,0,0,0,0,0,1,0},//7
		{0,0,0,0,0,0,0,0,0,0,1},//8
		{0,0,0,0,0,0,0,0,0,0,1},//9
		{0,0,0,0,0,0,0,0,0,0,0},//10
	};

	std::vector<size_t> out_vertex{ 1,2,3,4 };
	EXPECT_EQ(graph.detect_out_vertex(0), out_vertex);
	
	out_vertex.clear();
	out_vertex.emplace_back(5);
	EXPECT_EQ(graph.detect_out_vertex(1), out_vertex);

	out_vertex.clear();
	out_vertex.emplace_back(6);
	EXPECT_EQ(graph.detect_out_vertex(2), out_vertex);

	out_vertex.clear();
	out_vertex.emplace_back(6);
	EXPECT_EQ(graph.detect_out_vertex(3), out_vertex);

	out_vertex.clear();
	out_vertex.emplace_back(7);
	EXPECT_EQ(graph.detect_out_vertex(5), out_vertex);

	out_vertex.clear();
	out_vertex.emplace_back(8);
	EXPECT_EQ(graph.detect_out_vertex(6), out_vertex);

	out_vertex.clear();
	out_vertex.emplace_back(9);
	EXPECT_EQ(graph.detect_out_vertex(7), out_vertex);

	out_vertex.clear();
	out_vertex.emplace_back(10);
	EXPECT_EQ(graph.detect_out_vertex(8), out_vertex);

	out_vertex.clear();
	out_vertex.emplace_back(10);
	EXPECT_EQ(graph.detect_out_vertex(9), out_vertex);

	out_vertex.clear();
	EXPECT_EQ(graph.detect_out_vertex(10), out_vertex);
}

TEST(GraphTest, DFSColorTest)
{
	Graph<int, 11> graph{
		//   0 1 2 3 4 5 6 7 8 9 10
			{0,1,1,1,1,0,0,0,0,0,0},//0
			{0,0,0,0,0,1,0,0,0,0,0},//1
			{0,0,0,0,0,0,1,0,0,0,0},//2
			{0,0,0,0,0,0,1,0,0,0,0},//3
			{0,0,0,0,0,0,1,0,0,0,0},//4
			{0,0,0,0,0,0,0,1,0,0,0},//5
			{0,0,0,0,0,0,0,0,1,0,0},//6
			{0,0,0,0,0,0,0,0,0,1,0},//7
			{0,0,0,0,0,0,0,0,0,0,1},//8
			{0,0,0,0,0,0,0,0,0,0,1},//9
			{0,0,0,0,0,0,0,0,0,0,0},//10
	};

	graph.one_topo();

	auto p = std::find(std::begin(graph.color), std::end(graph.color), Color::COLOR_GRAY);
	EXPECT_EQ(p, std::end(graph.color));
	p = std::find(std::begin(graph.color), std::end(graph.color), Color::COLOR_WHITE);
	EXPECT_EQ(p, std::end(graph.color));
}

TEST(GraphTest, GenTopoNTimes)
{
	Graph<int, 11> graph{
		//   0 1 2 3 4 5 6 7 8 9 10
			{0,1,1,1,1,0,0,0,0,0,0},//0
			{0,0,0,0,0,1,0,0,0,0,0},//1
			{0,0,0,0,0,0,1,0,0,0,0},//2
			{0,0,0,0,0,0,1,0,0,0,0},//3
			{0,0,0,0,0,0,1,0,0,0,0},//4
			{0,0,0,0,0,0,0,1,0,0,0},//5
			{0,0,0,0,0,0,0,0,1,0,0},//6
			{0,0,0,0,0,0,0,0,0,1,0},//7
			{0,0,0,0,0,0,0,0,0,0,1},//8
			{0,0,0,0,0,0,0,0,0,0,1},//9
			{0,0,0,0,0,0,0,0,0,0,0},//10
	};

	size_t total_times{ 1 };
	std::set<std::vector<size_t>> topo_set{};
	for (size_t i{}; i < total_times; i++)
	{
		topo_set.insert(graph.one_topo());
	}
	//std::cout << "Random count: " << topo_set.size() << std::endl;
}

TEST(GraphTest, InitIndegree)
{
	Graph<int, 6> graph{
		//   0 1 2 3 4 5 
			{0,0,0,0,0,0}, // 0
			{0,0,0,0,0,0}, // 1
			{0,0,0,1,0,0}, // 2
			{0,1,0,0,0,0}, // 3
			{1,1,0,0,0,0}, // 4
			{1,0,1,0,0,0}, // 5
	};

	graph.init_indgree();
	std::array<int, 6> indegree_vec{ 2,2,1,1,0,0 };
	EXPECT_EQ(graph.indegree_vec, indegree_vec);
}
	
TEST(GraphTest, DecreaseIndegreeTest)
{
	Graph<int, 6> graph{
		//   0 1 2 3 4 5 
			{0,0,0,0,0,0}, // 0
			{0,0,0,0,0,0}, // 1
			{0,0,0,1,0,0}, // 2
			{0,1,0,0,0,0}, // 3
			{1,1,0,0,0,0}, // 4
			{1,0,1,0,0,0}, // 5
	};

	auto out_vertex = graph.detect_out_vertex(5);
	graph.init_indgree();
	graph.decrease_indegree(out_vertex);
	std::array<int, 6> indegree{ 1,2,0,1,0,0 };
	EXPECT_EQ(graph.indegree_vec, indegree);
}

TEST(GraphTest, IncreaseIndegreeTest)
{
	Graph<int, 6> graph{
		//   0 1 2 3 4 5 
			{0,0,0,0,0,0}, // 0
			{0,0,0,0,0,0}, // 1
			{0,0,0,1,0,0}, // 2
			{0,1,0,0,0,0}, // 3
			{1,1,0,0,0,0}, // 4
			{1,0,1,0,0,0}, // 5
	};

	auto out_vertex = graph.detect_out_vertex(5);
	graph.init_indgree();
	graph.decrease_indegree(out_vertex);
	graph.increase_indegree(out_vertex);
	std::array<int, 6> indegree{ 2,2,1,1,0,0 };
	EXPECT_EQ(graph.indegree_vec, indegree);
}

TEST(GraphTest, AllTopoSortsTest)
{
	Graph<int, 11> graph{
		//   0 1 2 3 4 5 6 7 8 9 10
			{0,1,1,1,1,0,0,0,0,0,0},//0
			{0,0,0,0,0,1,0,0,0,0,0},//1
			{0,0,0,0,0,0,1,0,0,0,0},//2
			{0,0,0,0,0,0,1,0,0,0,0},//3
			{0,0,0,0,0,0,1,0,0,0,0},//4
			{0,0,0,0,0,0,0,1,0,0,0},//5
			{0,0,0,0,0,0,0,0,1,0,0},//6
			{0,0,0,0,0,0,0,0,0,1,0},//7
			{0,0,0,0,0,0,0,0,0,0,1},//8
			{0,0,0,0,0,0,0,0,0,0,1},//9
			{0,0,0,0,0,0,0,0,0,0,0},//10
	};


	//auto all_topo_sorts = graph.all_topo();
	//std::cout << all_topo_sorts + 1 << std::endl;
	//std::cout << "All topo count: " << all_topo_sorts.size() << std::endl;
}

TEST(ReaderTest, SplitTest)
{
	Reader file("jackson.csv");

	std::string str{ "0,1,0,0,1,1," };
	auto splited_str = file.split(str, ',');
	std::vector<std::string> str_vec{ "0","1","0","0","1","1" };
	EXPECT_EQ(splited_str, str_vec);
}

TEST(ReaderTest, ReadFileTest)
{
	Reader file("jackson.csv");

	auto mat = file.read_file();
	std::cout << mat << std::endl;
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);	

	return RUN_ALL_TESTS();
}