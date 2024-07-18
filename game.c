enum levels {menu, base, map, structure};
enum levels currentLevel = map;

Gfx_Image* drawListMenu[20];
Gfx_Image* drawListBase[20];
Gfx_Image* drawListMap[1];
Gfx_Image* drawListStructure[20];

Vector2 pointsOfInterest[3];

int generateMapPointsOfInterest(){
	for (int i=0; i<3; ++i) {
		u64 randomThing = get_random() * PI64 * 2;
		float32 x = cos(randomThing);
		float32 y = sin(randomThing);
		Vector2 newPosition = {x, y};
		pointsOfInterest[i] = newPosition;
	};
};

void drawScene(){
	switch (currentLevel) {
		case menu: {
			// no menu fuk u
			break;
		};

		case base: {
			
			break;
		};
		case map: {
			// house pos = 0, 0
			size_t NumOfElems = sizeof(drawListMap)/sizeof(drawListMap[0]);
			for(int i = 0; i < NumOfElems; ++i) {
        		draw_image(drawListMap[i], v2(0, 0), v2(.1, .1), COLOR_WHITE);
    		}
			break;
		};
		case structure: {
			
			break;
		};
	};
}

bool check_crosshair_touching(){

}

int entry(int argc, char **argv) {
	window.title = STR("game thing");
	window.scaled_width = 1280; 
	window.scaled_height = 720; 
	window.x = 300;
	window.y = 300;
	window.clear_color = hex_to_rgba(0xf6d9a7ff);

	Gfx_Image *house_image = load_image_from_disk(fixed_string("../house.png"), get_heap_allocator());
	assert(house_image, "Failed loading house_image.png");
	drawListMap[0] = house_image;
	Gfx_Image *map_crosshair = load_image_from_disk(fixed_string("../map_crosshair.png"), get_heap_allocator());
	assert(map_crosshair, "Failed loading map_crosshair.png");

	Matrix4 camera_view = m4_scalar(1.0);
	Vector2 crosshair_pos = {0, 0};

	float64 last_time = os_get_current_time_in_seconds();

	//generateMapPointsOfInterest();
	
	while (!window.should_close) {
		reset_temporary_storage();
		const float64 fps_limit = 60;
		const float64 min_frametime = 1.0 / fps_limit;
		float64 now = os_get_current_time_in_seconds();
		float64 delta = now - last_time;
		if (delta < min_frametime) {
			os_high_precision_sleep((min_frametime-delta)*1000.0);
			now = os_get_current_time_in_seconds();
			delta = now - last_time;
		}
		last_time = now;
		os_update(); 
		if (is_key_just_pressed(KEY_ESCAPE)){
			window.should_close = true;
		}

		
		switch (currentLevel) {
			case menu: {
				// no menu fuk u
				break;
			};

			case base: {
				
				break;
			};

			case map: {
				const float32 cam_move_speed = 1.0;
				Vector2 cam_move_axis = v2(0, 0);
				if (is_key_down('A')) {
					cam_move_axis.x -= 1.0;
				}
				if (is_key_down('D')) {
				cam_move_axis.x += 1.0;
				}
				if (is_key_down('S')) {
					cam_move_axis.y -= 1.0;
				}
				if (is_key_down('W')) {
					cam_move_axis.y += 1.0;
				}
				cam_move_axis = v2_normalize(cam_move_axis);
				Vector2 cam_move = v2_mulf(cam_move_axis, delta * cam_move_speed);
				camera_view = m4_translate(camera_view, v3(v2_expand(cam_move), 0));
				draw_frame.view = camera_view;
				crosshair_pos = v2_add(crosshair_pos, cam_move);
				draw_image(map_crosshair, crosshair_pos, v2(.15, .15), COLOR_WHITE);
				if (crosshair_pos.x <= .5 && crosshair_pos.y <= .5) {

				}
				break;
			};

			case structure: {
				
				break;
			};
		};

		drawScene();
		

		//float64 now = os_get_current_time_in_seconds();
		//Matrix4 rect_xform = m4_scalar(1.0);
		//rect_xform         = m4_rotate_z(rect_xform, (f32)now);
		//rect_xform         = m4_translate(rect_xform, v3(-.25f, -.25f, 0));
		//draw_rect_xform(rect_xform, v2(.5f, .5f), COLOR_RED);
		
		gfx_update();
	}

	return 0;
}