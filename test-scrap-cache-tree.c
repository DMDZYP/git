#include "cache.h"
#include "lockfile.h"
#include "tree.h"
#include "cache-tree.h"

static struct lock_file index_lock;

int main(int ac, char **av)
{
	struct strbuf err = STRBUF_INIT;
	if (hold_locked_index(&index_lock, &err) < 0)
		die("%s", err.buf);
	if (read_cache() < 0)
		die("unable to read index file");
	active_cache_tree = NULL;
	if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
		die("unable to write index file");
	strbuf_release(&err);
	return 0;
}
