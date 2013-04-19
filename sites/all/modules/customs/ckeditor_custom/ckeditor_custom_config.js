CKEDITOR.editorConfig = function(config)
{

  //config.extraPlugins += 'devtools';
  config.resize_dir = 'vertical';
  config.autoParagraph = false;
  config.toolbarCanCollapse = false;
  config.pasteFromWordRemoveStyles = true;
  config.forcePasteAsPlainText = true;
  config.docType = '<!doctype html>';

  config.removeFormatTags = 'big,del,dfn,ins,kbd,samp,tt,var';

  // BCIS Colours added to 000
  config.colorButton_colors = '6ec042,00905f,006c76,0196be,a42e2a,ca322d,ca322d,f4762a,000,800000,8B4513,2F4F4F,008080,000080,4B0082,696969,B22222,A52A2A,DAA520,006400,40E0D0,0000CD,800080,808080,F00,FF8C00,FFD700,008000,0FF,00F,EE82EE,A9A9A9,FFA07A,FFA500,FFFF00,00FF00,AFEEEE,ADD8E6,DDA0DD,D3D3D3,FFF0F5,FAEBD7,FFFFE0,F0FFF0,F0FFFF,F0F8FF,E6E6FA,FFF';

  // Styles dropdown
  config.stylesSet = [

    /* Buttons */
    {name: 'Button white', element: 'span', attributes: {'class' : 'btn'}},
    {name: 'Button blue', element: 'span', attributes: {'class' : 'btn btn-primary'}},
    {name: 'Button green', element: 'span', attributes: {'class' : 'btn btn-success'}},
    {name: 'Button orange', element: 'span', attributes: {'class' : 'btn btn-warning'}},
    {name: 'Button danger', element: 'span', attributes: {'class' : 'btn btn-danger'}},
    {name: 'Button black', element: 'span', attributes: {'class' : 'btn btn-inverse'}},

    /* Well */
    {name: 'Well', element: 'span', attributes: {'class' : 'well'}},

    /* Highlight */
    {name: 'Highlight yellow', element: 'span', attributes: {'class' : 'alert alert-warning'}},
    {name: 'Highlight red', element: 'span', attributes: {'class' : 'alert alert-error'}},
    {name: 'Highlight green', element: 'span', attributes: {'class' : 'alert alert-success'}}

  ];

  // What fonts we're going to use
  config.font_names =
    'News cycle;' +
    'News regular;' +
    'Helvetica/Helvetica, Arial, sans-serif;' +
    'Georgia/Georgia, serif;' +
    'Times New Roman/Times New Roman, Times, serif;' +
    'Just Me Again Down Here;' +
    'Courier New/Courier New, Courier, monospace;';

};
