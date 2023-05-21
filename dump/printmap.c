void	console_print_map(t_map *map)
{
	t_tiles	*e;

	while (map)
	{
		console_log("Map name = %s\n", map->name);
		console_log("\nMap size = %i x %i\n", map->width, map->height);
		e = map->tiles;
		while (e)
		{
			console_log("%c", e->type);
			if (e->next && e->next->y > e->y)
				console_log("\n");
			e = e->next;
		}
		console_log("\n");
		map = map->next;
	}
}