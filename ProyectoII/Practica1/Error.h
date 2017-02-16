#pragma once
#include <string>
class Error { // Clase raíz:
protected:
	std:: string m;
public:
	Error(std:: string const& am) : m(am) {};
	virtual ~Error() {}; // noexcept
	const std::string & mensaje() const { return m; }; // noexcept
};

// Error en las texturas normales----------------------------------------------------------------------------------------------------------------
class EInitSDL : public Error {
public:
	EInitSDL(std::string const& am) : Error(am) {};
};
class ELoadTexture : public Error {
public:
	ELoadTexture(std::string const& am) : Error(am) {};
};
class EInitWindow : public Error {
public:
	EInitWindow(std::string const& am) : Error(am) {};
};
class EInitRender : public Error {
public:
	EInitRender(std::string const& am) : Error(am) {};
};
// Error en el sonido----------------------------------------------------------------------------------------------------------------------------
class EInitMixer : public Error {
public:
	EInitMixer(std::string const& am) : Error(am) {};
};

class ELoadMusic : public Error {
public:
	ELoadMusic(std::string const& am) : Error(am) {};
};

class ELoadFX : public Error {
public:
	ELoadFX(std::string const& am) : Error(am) {};
};

// Error en las fuentes------------------------------------------------------------------------------------------------------------------------
class EInitTTF : public Error {
public:
	EInitTTF(std::string const& am) : Error(am) {};
};

class ELoadFont : public Error {
public:
	ELoadFont(std::string const& am) : Error(am) {};
};
