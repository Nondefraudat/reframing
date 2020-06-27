#pragma once

class Entity
{
	const char** title;
	const char** description;

public:
	Entity(const char** title, const char** description);

	const char** getTitle();
	const char** getDescription();

	void setTitle(const char** title);
	void setDescription(const char** description);
};

