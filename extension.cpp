#include "extension.h"

using namespace php;
using namespace std;

PHPX_FUNCTION(flashtext)
{
	if (args[0].type() == IS_ARRAY && args[1].type() == IS_STRING) {
		Cflashtext flashtext = Cflashtext();
		Array keyWordsArr(args[0]);
		flashtext.learn(keyWordsArr);
		String content(args[1]);
		retval = flashtext.match(content);
	}
	else {
		retval = false;
	}
}


PHPX_METHOD(flashtext, learn)
{
	Cflashtext* flashtext_obj = new Cflashtext();
	Array keyWordsArr(args[0]);
	flashtext_obj->learn(keyWordsArr);
	_this.oSet<Cflashtext>("flashtext_ptr", "ResourceFlashtext", flashtext_obj);
}

PHPX_METHOD(flashtext, match)
{
	Cflashtext* flashtext_obj = _this.oGet<Cflashtext>("flashtext_ptr", "ResourceFlashtext");
	String content(args[0]);
	retval = flashtext_obj->match(content);
}

void flashtext_dtor(zend_resource* res)
{
	Cflashtext* s = static_cast<Cflashtext*>(res->ptr);
	delete s;
}

PHPX_EXTENSION()
{
    Extension *extension = new Extension("flashtext", "0.0.1");

    extension->onStart = [extension]() noexcept
    {
        extension->registerConstant("CPP_EXT_VERSION", 1002);

        Class *c = new Class("flashtext");
        c->addMethod(PHPX_ME(flashtext, learn));
        c->addMethod(PHPX_ME(flashtext, match));
        extension->registerClass(c);

		extension->registerResource("ResourceFlashtext", flashtext_dtor);

    };

	extension->registerFunction(PHPX_FN(flashtext));

    extension->info(
    {
        "flashtext support", "enabled"
    },
    {
        { "author", "colin" },
        { "version", extension->version },
        { "date", "2019-08-26" },
    });

    return extension;
}
