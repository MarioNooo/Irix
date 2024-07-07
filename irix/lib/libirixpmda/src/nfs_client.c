#ident "$Id: nfs_client.c,v 1.16 1997/07/23 04:21:14 chatz Exp $"

/*
 * Handle metrics for cluster nfs_client (12)
 *
 * Code built by newcluster on Mon Jun  6 12:54:42 EST 1994
 */

#include <sys/types.h>
#include <sys/sysmp.h>
#include <sys/sysinfo.h>
#include <sys/fs/nfs_stat.h>
#include <syslog.h>
#include "pmapi.h"
#include "impl.h"
#include "./cluster.h"

static struct clstat	clstat;
#define N_NFSREQS 18

static pmMeta		meta[] = {
/* irix.nfs.client.badcalls */
  { (char *)&clstat.nbadcalls, { PMID(1,12,1), PM_TYPE_32, PM_INDOM_NULL, PM_SEM_COUNTER, {0,0,1,0,0,PM_COUNT_ONE} } },
/* irix.nfs.client.calls */
  { (char *)&clstat.ncalls, { PMID(1,12,2), PM_TYPE_32, PM_INDOM_NULL, PM_SEM_COUNTER, {0,0,1,0,0,PM_COUNT_ONE} } },
/* irix.nfs.client.nclget */
  { (char *)&clstat.nclgets, { PMID(1,12,3), PM_TYPE_32, PM_INDOM_NULL, PM_SEM_COUNTER, {0,0,1,0,0,PM_COUNT_ONE} } },
/* irix.nfs.client.nclsleep */
  { (char *)&clstat.nclsleeps, { PMID(1,12,4), PM_TYPE_32, PM_INDOM_NULL, PM_SEM_COUNTER, {0,0,1,0,0,PM_COUNT_ONE} } },
/* irix.nfs.client.reqs */
  { (char *)&clstat.reqs[0], { PMID(1,12,5), PM_TYPE_32, PM_INDOM_NFSREQ, PM_SEM_COUNTER, {0,0,1,0,0,PM_COUNT_ONE} } }
};

static int		nmeta = (sizeof(meta)/sizeof(meta[0]));
static int		fetched;
static int		direct_map = 1;

void nfs_client_init(int reset)
{
    int		i;
    int		indomtag; /* Constant from descr in form */

    if (reset)
	return;

    for (i = 0; i < nmeta; i++) {
        indomtag = meta[i].m_desc.indom;
	if (direct_map && meta[i].m_desc.pmid != PMID(1,12,i+1)) {
	    direct_map = 0;
	    __pmNotifyErr(LOG_WARNING, 
			 "nfs_client_init: direct map disabled @ meta[%d]", i);
	}	
        if (indomtag == PM_INDOM_NULL)
            continue;
        if (indomtag < 0 || indomtag >= PM_INDOM_NEXT) {
            __pmNotifyErr(LOG_ERR, "nfs_client_init: bad instance domain (%d) for metric %s\n",
                         indomtag, pmIDStr(meta[i].m_desc.pmid));
            continue;
        }
        /* Replace tag with it's indom */
        meta[i].m_desc.indom = indomtab[indomtag].i_indom;
    }

    for (i = 0; i < nmeta; i++)
	meta[i].m_offset = (char *)((ptrdiff_t)(meta[i].m_offset - (char *)&clstat));
}

void nfs_client_fetch_setup(void)
{
    fetched = 0;
}

int nfs_client_desc(pmID pmid, pmDesc *desc)
{
    int		i;

    for (i = 0; i < nmeta; i++) {
	if (pmid == meta[i].m_desc.pmid) {
	    *desc = meta[i].m_desc;	/* struct assignment */
	    return 0;
	}
    }
    return PM_ERR_PMID;
}

int nfs_client_fetch(pmID pmid, __pmProfile *profp, pmVPCB *vpcb)
{
    int		i;
    int		k;
    int		sts;
    pmAtomValue	av;
    pmAtomValue	*avp;
    int		nval;
    static int	interesting[N_NFSREQS];

    if (direct_map) {
	__pmID_int       *pmidp = (__pmID_int *)&pmid;
        i = pmidp->item - 1;
	if (i < nmeta && pmid == meta[i].m_desc.pmid)
	    goto doit;

	__pmNotifyErr(LOG_WARNING, 
		     "nfs_client_fetch: direct mapping failed for %s (!= %s)\n",
		     pmIDStr(pmid), pmIDStr(meta[i].m_desc.pmid));
	direct_map = 0;
    }

    for (i = 0; i < nmeta; i++)
	if (pmid == meta[i].m_desc.pmid)
	    break;

    if (i >= nmeta) {
	vpcb->p_nval = 0;
	return PM_ERR_PMID;
    }

 doit:

    if (fetched == 0) {
#ifdef MPSA_CLSTAT
	if (sysmp(MP_SAGET, MPSA_CLSTAT, &clstat, sizeof(clstat)) < 0) {
#else
        errno = PM_ERR_PMID;
	if (1) {
#endif
	    __pmNotifyErr(LOG_WARNING, "nfs_client_fetch: %s", pmErrStr(-errno));
	    return -errno;
	}
	fetched = 1;
    }
	
    switch (pmid) {
    case PMID(1,12,5):		/* irix.nfs.client.reqs */
	vpcb->p_nval = 0;
	for (k=0; k < N_NFSREQS; k++) {
	    if (interesting[k] = __pmInProfile(meta[i].m_desc.indom, profp, k))
		vpcb->p_nval++;
	}
	sizepool(vpcb);
	nval = 0;
	for (k=0; k < N_NFSREQS; k++) {
	    if (interesting[k] == 0)
		continue;
	    av.ul = clstat.reqs[k];
	    if ((sts = __pmStuffValue(&av, 0, &vpcb->p_vp[nval], meta[i].m_desc.type)) < 0)
		break;
	    vpcb->p_vp[nval++].inst = k;
	}
	vpcb->p_valfmt = sts;
	return sts;
	
    default:			/* irix.nfs.client.anything_other_than_reqs */
	vpcb->p_nval = 1;
	vpcb->p_vp[0].inst = PM_IN_NULL;
	avp = (pmAtomValue *)&((char *)&clstat)[(ptrdiff_t)meta[i].m_offset];
	if ((sts = __pmStuffValue(avp, 0, vpcb->p_vp, meta[i].m_desc.type)) < 0)
	    return sts;
	vpcb->p_valfmt = sts;
	/* success */
	return 0;
    }
}
