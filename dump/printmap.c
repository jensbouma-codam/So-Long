void	console_print_map(t_map *map)
{
	t_tiles	*e;

	while (map)
	{
		console_log("Map name = %s\n", map->name);
		console_log("\nMap size = %i x %i\n", map->width, map->height);
		e = map->tile;
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


// print("Map name = %s\n", level->name);
	// print("\nMap size = %i x %i\n", level->w, level->h);
	// e = level->tile;
	// while (e)
	// {
	// 	if (e->reachable)
	// 		print("*");
	// 	else
	// 		print("%c", e->type);
	// 	if (e->next && e->next->y > e->y)
	// 		print("\n");
	// 	e = e->next;
	// }
	// print("\n");