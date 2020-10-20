class DZLUIItemCreator
{

	Widget layoutRoot;
	
    void DZLUIItemCreator(string layoutRootPath) {
		this.layoutRoot = GetGame().GetWorkspace().CreateWidgets(layoutRootPath);
	}

	Widget GetLayoutRoot() {
	    return this.layoutRoot;
	}

    TextListboxWidget GetTextListboxWidget(string name) {
        TextListboxWidget widget = TextListboxWidget.Cast(layoutRoot.FindAnyWidget(name));

        return widget;
    }

    XComboBoxWidget GetXComboBoxWidget(string name) {
        return XComboBoxWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    EditBoxWidget GetEditBoxWidget(string name) {
        return EditBoxWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    ItemPreviewWidget GetItemPreviewWidget(string name) {
        return ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    MultilineTextWidget GetMultilineTextWidget(string name) {
        return MultilineTextWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    TextWidget GetTextWidget(string name) {
        return TextWidget.Cast(layoutRoot.FindAnyWidget(name));
    }
	
    MapWidget GetMapWidget(string name) {
        return MapWidget.Cast(layoutRoot.FindAnyWidget(name));
    }

    ButtonWidget GetButtonWidget(string name) {
        ButtonWidget button =  ButtonWidget.Cast(layoutRoot.FindAnyWidget(name));
        return button;
    }
}