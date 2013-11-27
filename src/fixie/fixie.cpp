#include "fixie/fixie.h"

#include "fixie_lib/debug.hpp"
#include "fixie_lib/context.hpp"

extern "C"
{

fixie_context FIXIE_APIENTRY fixie_create_context()
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::create_context();
        fixie::set_current_context(ctx.get());
        return ctx.get();
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
        return nullptr;
    }
    catch (...)
    {
        UNREACHABLE();
        return nullptr;
    }
}

void FIXIE_APIENTRY fixie_destroy_context(fixie_context ctx)
{
    try
    {
        fixie::destroy_context(reinterpret_cast<fixie::context*>(ctx));
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

void FIXIE_APIENTRY fixie_set_context(fixie_context ctx)
{
    try
    {
        fixie::set_current_context(reinterpret_cast<fixie::context*>(ctx));
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

fixie_context FIXIE_APIENTRY fixie_get_context()
{
    try
    {
        std::shared_ptr<fixie::context> ctx = fixie::get_current_context();
        return ctx.get();
    }
    catch (const fixie::context_error& e)
    {
        fixie::log_context_error(e);
        return nullptr;
    }
    catch (...)
    {
        UNREACHABLE();
        return nullptr;
    }
}

void FIXIE_APIENTRY fixie_terminate()
{
    try
    {
        fixie::terminate();
    }
    catch (...)
    {
        UNREACHABLE();
    }
}

}
