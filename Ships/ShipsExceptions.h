#pragma once
#include <string>

class ShipsException : public std::exception
{
	std::string message;
public:
	explicit ShipsException(const std::string& message);

	const char* what() const noexcept override;
};

class object_already_contained : public ShipsException 
{
	using ShipsException::ShipsException;
};

class index_out_of_range : public ShipsException 
{
	using ShipsException::ShipsException;
};

class no_object_found : public ShipsException 
{
	using ShipsException::ShipsException;
};

class font_load_error : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_board_size : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_field_size : public ShipsException 
{
	using ShipsException::ShipsException;
};

class field_out_of_range : public ShipsException 
{
	using ShipsException::ShipsException;
};

class field_not_found : public ShipsException 
{
	using ShipsException::ShipsException;
};

class field_not_empty : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_coordinate : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_range_value : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_damage_value : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_missle_id : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_player_index : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_winner_player : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_line_in_file : public ShipsException 
{
	using ShipsException::ShipsException;
};

class key_not_found : public ShipsException
{
	using ShipsException::ShipsException;
};

class invalid_max_moves_value : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_movement_value : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_hit_point_value : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_name : public ShipsException 
{
	using ShipsException::ShipsException;
};

class improper_vector_size : public ShipsException 
{
	using ShipsException::ShipsException;
};

class space_in_name_error : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_height : public ShipsException 
{
	using ShipsException::ShipsException;
};

class field_occupied : public ShipsException 
{
	using ShipsException::ShipsException;
};

class file_failed_string_to_int_convertion : public ShipsException 
{
	using ShipsException::ShipsException;
};

class invalid_file_format : public ShipsException 
{
	using ShipsException::ShipsException;
};
