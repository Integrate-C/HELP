enum levels {menu, base, map, structure};
enum levels currentLevel = map;

entityStruct* drawListMenu[20];
entityStruct* drawListBase[20];
entityStruct* drawListMap[1];
entityStruct* drawListStructure[20];

entityStruct pointsOfInterest[3];

string poiNames[6];
string poiDescriptions[6];

typedef struct {
	Vector2 Pos;
    Draw_Quad Matrix;
	Gfx_Image* Image;
	string Name;
	string Description;
} entityStruct;

entityStruct newEnitityStruct(){
    entityStruct newStruct;
    newStruct.Pos = v2(0, 0);
    return newStruct;
}

int generateMapPointsOfInterest(){
	for (int i=0; i<3; ++i) {
		//seed_for_random = os_get_current_cycle_count();
		//u64 angle = get_random_from_seed(randomSeed) * PI64 * 2;
		//test_random_distribution()
		u64 angle = get_random_float32_in_range(0, 359) * PI64 * 2;
		//all of these.. every single one of these.. NONE OF ANY OF THESE
		//NONE OF THEM FUCKING GIVE A TRUE RANDOM DISTRIBUTION AT BUILD, AND IM GOING TO FUCKING LOSE IT
		float32 x = cos(angle) * 50;
		float32 y = sin(angle) * 50;
		Vector2 newPosition = {x, y};
		pointsOfInterest[i].Pos = newPosition;
		int dataGen = get_random_int_in_range(0, 6);
		pointsOfInterest[i].Name = poiNames[dataGen];
		pointsOfInterest[i].Description = poiDescriptions[dataGen];
		log("Name: %s, Description: %s", poiNames[dataGen], poiDescriptions[dataGen]);
	};
};

void drawScene(){
	switch (currentLevel) {
		case menu: {
			
			break;
		};
		case base: {
			
			break;
		};
		case map: {
			size_t NumOfElems = sizeof(drawListMap)/sizeof(drawListMap[0]);
			for(int i = 0; i < NumOfElems; ++i) {
				draw_image(drawListMap[i]->Image, v2(0, 0), v2(9, 7), COLOR_WHITE);
			}
			NumOfElems = sizeof(pointsOfInterest)/sizeof(pointsOfInterest[0]);
			for (int i=0; i < NumOfElems; ++i) {
				//draw_image_xform();
				draw_image(pointsOfInterest[i].Image, pointsOfInterest[i].Pos, v2(10, 17), COLOR_WHITE);
			}
			break;
		};
		case structure: {
			
			break;
		};
	};
}

bool checkCollision(entityStruct a, entityStruct b){
	//using AABB collsion checks
	//if (a.Pos.x > b.pos.x + b)

}

int entry(int argc, char **argv) {
	window.title = STR("game thing");
	window.scaled_width = 1280; 
	window.scaled_height = 720; 
	window.x = 300;
	window.y = 300;
	window.clear_color = hex_to_rgba(0xf6d9a7ff);

	Gfx_Image *house_image = load_image_from_disk(fixed_string("../house.png"), get_heap_allocator());
	assert(house_image, "ruh roh");
	entityStruct house_struct; //= newEnitityStruct();
	house_struct.Image = house_image;
	drawListMap[0] = &house_struct;

	Gfx_Image *map_crosshair = load_image_from_disk(fixed_string("../map_crosshair.png"), get_heap_allocator());
	assert(map_crosshair, "ruh roh");
	entityStruct crosshair; //= newEnitityStruct();
	crosshair.Image = map_crosshair;

	Gfx_Image *point_of_intereset_icon = load_image_from_disk(fixed_string("../point_of_interest.png"), get_heap_allocator());
	assert(point_of_intereset_icon, "ruh roh");
	pointsOfInterest[0].Image = point_of_intereset_icon;
	pointsOfInterest[1].Image = point_of_intereset_icon;
	pointsOfInterest[2].Image = point_of_intereset_icon;

	poiNames[0] = STR("Abandoned House");
	poiNames[1] = STR("Abandoned Supermarket");
	poiNames[2] = STR("Old Quarry");
	poiNames[3] = STR("Ruined Construction Site");
	poiNames[4] = STR("Jonty's Bedroom");
	poiNames[5] = STR("Old Factory");

	poiDescriptions[0] = STR("An Old Abandoned House.");
	poiDescriptions[1] = STR("An Old Abandoned Supermarket.");
	poiDescriptions[2] = STR("The old quarry, used to run deep until it flooded.");
	poiDescriptions[3] = STR("A Decaying Contruction Site.");
	poiDescriptions[4] = STR("The man cave of an infamous gooner.");
	poiDescriptions[5] = STR("Wonder what they used to make here.");
	
	Matrix4 camera_view = m4_scalar(1.0);
	float64 last_time = os_get_current_time_in_seconds();

	generateMapPointsOfInterest();
	float zoom = 5;

	while (!window.should_close) {
		reset_temporary_storage();

		draw_frame.projection = m4_make_orthographic_projection(window.width * -0.5, window.width * 0.5, window.height * -0.5, window.height * 0.5, -1, 10);
		
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
				const float32 cam_move_speed = 50.0;
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
				Matrix4 scale = m4_make_scale(v3(1.0/zoom, 1.0/zoom, 1));
				draw_frame.view = m4_mul(camera_view, scale);
				crosshair.Pos = v2_add(crosshair.Pos, cam_move);
				drawScene();
				//range2f_make();
				Draw_Quad crosshairQuad = *draw_image(crosshair.Image, crosshair.Pos, v2(7, 7), COLOR_WHITE);
				
				//if (checkCollision()) {
					
				//}
			};
			case structure: {
				
				break;
			};
		};

		
		

		//float64 now = os_get_current_time_in_seconds();
		//Matrix4 rect_xform = m4_scalar(1.0);
		//rect_xform         = m4_rotate_z(rect_xform, (f32)now);
		//rect_xform         = m4_translate(rect_xform, v3(-.25f, -.25f, 0));
		//draw_rect_xform(rect_xform, v2(.5f, .5f), COLOR_RED);
		
		gfx_update();
	}

	return 0;
}