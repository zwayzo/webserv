#include "../multuplixing/multuplixing.hpp"
#include "post.hpp"

void post_contentLenght(std::map<int, client>::iterator iter, int i, int nbytes)
{
    if (nbytes != 0 && iter->second.req.method <= 0)
        getMethodes(iter->second.req.buff, &iter->second);
    else if (nbytes == -1)
        throw ("error in recv\n");
    if (iter->second.req.post == 1)
        post(iter, i, nbytes);
    printf("%lld|%lld\n", iter->second.req.track, iter->second.req.contentLenght);
                        
}
