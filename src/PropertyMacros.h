#ifndef PROPERTYMACROS_H
#define PROPERTYMACROS_H

#define CONSTANT_PROPERTY_H(type, name)           \
    public:                                      \
    Q_PROPERTY(type name READ get##name CONSTANT) \
    type get##name() const { return name; }       \
    static const type name;

#define CONSTANT_PROPERTY_CPP(classname, type, name, value) \
    const type classname::name = value;

#define CONSTANT_PROPERTY(type, name, value)      \
    public:                                      \
    Q_PROPERTY(type name READ get##name CONSTANT) \
    type get##name() const { return name; }       \
    static const type name = value;

#define CHANGING_PROPERTY(type, name)                                                       \
    public:                                                                               \
    Q_PROPERTY(type name READ get##name WRITE set##name NOTIFY signal##name##Changed) \
    type get##name() const { return name; }                                           \
    void set##name(const type& aValue) {                                              \
        if (aValue != name) {                                                         \
            name = aValue;                                                            \
            emit signal##name##Changed();                                             \
        }                                                                             \
    }                                                                                 \
    private:                                                                           \
    type name;

#endif //PROPERTYMACROS_H
