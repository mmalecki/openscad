#pragma once

#include "parametervirtualwidget.h"
#include "ui_parametertext.h"

class ParameterText : public ParameterVirtualWidget, Ui::ParameterText
{
	Q_OBJECT

public:
	ParameterText(QWidget *parent, StringParameter *parameter, DescriptionStyle descriptionStyle);
	void setValue() override;
	void valueApplied() override;

protected slots:
	void onEdit(const QString &text);
	void onEditingFinished();

private:
	StringParameter* parameter;
	boost::optional<std::string> lastSent;
	boost::optional<std::string> lastApplied;
};
