#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Polygon_2.h>
#include "../inc/head.h"
 

struct FaceInfo2
{
	FaceInfo2(){}
	int nesting_level;

	bool in_domain(){ 
		return nesting_level%2 == 1;
	}
};


typedef CGAL::Exact_predicates_inexact_constructions_kernel       K;
typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned,K>    Vb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo2,K>    Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>        Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_predicates_tag                                Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>  CDT;
typedef CDT::Point                                                Point;
typedef CGAL::Polygon_2<K>                                        Polygon_2;
typedef std::vector< std::pair<Point,unsigned> >                  Points;


/*
 * to get data from database
 * by hzs
 * 
 */
//--------------------------------------------
void mark_domains(CDT& ct, CDT::Face_handle start, int index, std::list<CDT::Edge>& border );
void mark_domains(CDT& cdt);
void insert_polygon(CDT& cdt,const Polygon_2& polygon);






//--------------------------------------------
void mark_domains(CDT& ct, 	CDT::Face_handle start, int index, std::list<CDT::Edge>& border )
{
	if(start->info().nesting_level != -1){
		return;
	}
	std::list<CDT::Face_handle> queue;
	queue.push_back(start);

	while(! queue.empty()){
		CDT::Face_handle fh = queue.front();
		queue.pop_front();
		if(fh->info().nesting_level == -1){
			fh->info().nesting_level = index;
			for(int i = 0; i < 3; i++){
				CDT::Edge e(fh,i);
				CDT::Face_handle n = fh->neighbor(i);
				if(n->info().nesting_level == -1){
					if(ct.is_constrained(e)) border.push_back(e);
					else queue.push_back(n);
				}
			}
		}
	}
}

//explore set of facets connected with non constrained edges,
//and attribute to each such set a nesting level.
//We start from facets incident to the infinite vertex, with a nesting
//level of 0. Then we recursively consider the non-explored facets incident 
//to constrained edges bounding the former set and increase the nesting level by 1.
//Facets in the domain are those with an odd nesting level.
	void
mark_domains(CDT& cdt)
{
	for(CDT::All_faces_iterator it = cdt.all_faces_begin(); it != cdt.all_faces_end(); ++it){
		it->info().nesting_level = -1;
	}

	std::list<CDT::Edge> border;
	mark_domains(cdt, cdt.infinite_face(), 0, border);
	while(! border.empty()){
		CDT::Edge e = border.front();
		border.pop_front();
		CDT::Face_handle n = e.first->neighbor(e.second);
		if(n->info().nesting_level == -1){
			mark_domains(cdt, n, e.first->info().nesting_level+1, border);
		}
	}
}

void insert_polygon(CDT& cdt,const Polygon_2& polygon){
	int indices = 0;
	if ( polygon.is_empty() ) return;
	CDT::Vertex_handle v_prev=cdt.insert(*CGAL::cpp11::prev(polygon.vertices_end()));
	for (Polygon_2::Vertex_iterator vit=polygon.vertices_begin()+1;
			vit!=polygon.vertices_end();++vit)
	{
		CDT::Vertex_handle vh=cdt.insert(*vit);
		//    std::cout<<*vit<<std::endl;
		cdt.insert_constraint(vh,v_prev);
		vh->info() = indices;
		indices ++;
		v_prev=vh;
	} 
}

int polygon_traingle(POINT_LATLON_Z *in_point, int p_len, int index[], int *index_len)
{
	Polygon_2 polygon;
	for(int i = 0; i < p_len; i ++)
	{
		polygon.push_back(Point(in_point[i].coord.lon_deg, in_point[i].coord.lat_deg));
	}
	CDT cdt;
	insert_polygon(cdt, polygon);

	//Mark facets that are inside the domain bounded by the polygon
	mark_domains(cdt);
	int k = 0;
   for (CDT::Finite_faces_iterator fit=cdt.finite_faces_begin();
	   fit!=cdt.finite_faces_end();
	   ++fit)
   {
		if ( fit->info().in_domain() )
		{
			index[k] = fit->vertex(0)->info();
			index[k + 1] = fit->vertex(1)->info();
			index[k + 2] = fit->vertex(2)->info();
			index[k + 3] = -1;
			k += 4;
		}
   }
	*index_len = k;
	return 0;
}

int polygon_traingle(POINT_LATLON *in_point, int p_len, int index[], int *index_len)
{
	Polygon_2 polygon;
	for(int i = 0; i < p_len; i ++)
	{
		polygon.push_back(Point(in_point[i].lon_deg, in_point[i].lat_deg));
	}
	CDT cdt;
	insert_polygon(cdt, polygon);

	//Mark facets that are inside the domain bounded by the polygon
	mark_domains(cdt);
	int k = 0;
   for (CDT::Finite_faces_iterator fit=cdt.finite_faces_begin();
	   fit!=cdt.finite_faces_end();
	   ++fit)
   {
		if ( fit->info().in_domain() )
		{
			index[k] = fit->vertex(0)->info();
			index[k + 1] = fit->vertex(1)->info();
			index[k + 2] = fit->vertex(2)->info();
			index[k + 3] = -1;
			k += 4;
		}
   }
	*index_len = k;
	return 0;
}
