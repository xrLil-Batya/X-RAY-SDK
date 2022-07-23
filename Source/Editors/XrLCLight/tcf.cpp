#include	"stdafx.h"
#include	"tcf.h"
#include	"net_stream.h"
void	_TCF::barycentric	(Fvector2 &P, float &u, float &v, float &w)
{
	Fvector2 	kV02; kV02.sub(uv[0],uv[2]);
	Fvector2 	kV12; kV12.sub(uv[1],uv[2]);
	Fvector2 	kPV2; kPV2.sub(P,    uv[2]);

	float		fM00 = kV02.dot(kV02);
	float		fM01 = kV02.dot(kV12);
	float		fM11 = kV12.dot(kV12);
	float		fR0  = kV02.dot(kPV2);
	float		fR1  = kV12.dot(kPV2);
	float		fDet = fM00*fM11 - fM01*fM01;

	u			= (fM11*fR0 - fM01*fR1)/fDet;
	v			= (fM00*fR1 - fM01*fR0)/fDet;
	w			= 1.0f - u - v;
}
//	Fvector2			uv	[3];
void	_TCF::read		( INetReader	&r )
{
	r.r(uv, sizeof(uv) );
}
void	_TCF::write		( IWriter	&w ) const
{
	w.w(uv, sizeof(uv) );
}

void _TCF::readReader(IReader& r)
{  
	r.r(uv, sizeof(uv));
}

void _TCF::ReadLTX(CInifile* file, LPCSTR sec, LPCSTR pref)
{
	uv[0] = file->r_fvector2(sec, "v1");
	uv[1] = file->r_fvector2(sec, "v2");
	uv[2] = file->r_fvector2(sec, "v3");
}

void _TCF::WriteLTX(CInifile* file, LPCSTR sec, LPCSTR pref)
{
	string32 pr;
	xr_strcpy(pr, pref);
	xr_strcat(pr, "v1");
	file->w_fvector2(sec, pr, uv[0]);
	xr_strcpy(pr, pref);
	xr_strcat(pr, "v2");
	file->w_fvector2(sec, pr, uv[1]);
	xr_strcpy(pr, pref);
	xr_strcat(pr, "v3");
	file->w_fvector2(sec, pr, uv[2]);
}

bool _TCF::similar(    const _TCF &_tc, float eps /*= EPS*/  ) const
{
	return	uv[0].similar( _tc.uv[0], eps )&&
			uv[1].similar( _tc.uv[1], eps )&&
			uv[2].similar( _tc.uv[2], eps );
}
